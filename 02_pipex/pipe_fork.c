/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:49:18 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 21:26:41 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Creates a pipe for every pair of commands and sets up
the in and out file descriptor in the command.
Then sets up the fds to the first and last command as
the ones of the given files.
*/
void	create_commands(t_pipe *p, int ac, char **av)
{
	int	fd_p[2];
	int	i;

	i = -1;
	while (++i < p->n_cmds - 1)
	{
		if (pipe(fd_p) == -1)
			ft_exit(NULL, 1);
		p->cmds[i].fd_out = fd_p[1];
		p->cmds[i + 1].fd_in = fd_p[0];
	}
	if (!p->here_doc)
	{
		p->cmds[0].fd_in = open(av[1], O_RDONLY);
		if (p->cmds[0].fd_in < 0)
			ft_error(av[1], strerror(errno));
		p->cmds[p->n_cmds - 1].fd_out = open(av[ac - 1], \
			O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (p->cmds[p->n_cmds - 1].fd_out < 0)
			ft_error(av[1], strerror(errno));
	}
	else
		handle_here_doc(p, av);
	if (p->cmds[0].fd_in == -1 || p->cmds[p->n_cmds - 1].fd_out == -1)
		free_invalid_file(p);
}

void	ft_fork(t_pipe *p)
{
	int		i;

	i = 0;
	while (i < p->n_cmds)
	{
		p->process[i] = fork();
		if (p->process[i] == -1)
			ft_exit(NULL, 1);
		if (p->process[i] == 0)
		{
			if (!p->cmds[i].args)
				ft_exit("pipex: No arguments given\n", 1);
			ft_exec_cmd(p, &p->cmds[i]);
		}
		i++;
	}
}

/*
Closing parent processes that are not the first and last
Can find them checking if their fd_out == 1 or the fd_in == 0
*/
void	close_parents(t_pipe *p)
{
	int		i;
	int		ret;
	t_cmd	*parent;

	i = 0;
	while (i < p->n_cmds)
	{
		ret = wait(NULL);
		parent = get_cmd(p, ret);
		if (parent)
		{
			if (parent->fd_out != 1)
				close(parent->fd_out);
			if (parent->fd_in != 0)
				close(parent->fd_in);
		}
		i++;
	}
}

void	ft_exec_cmd(t_pipe *p, t_cmd *cmd)
{
	if (dup2(cmd->fd_in, 0) == -1 || dup2(cmd->fd_out, 1) == -1)
		exit(1);
	close_fd(p);
	if (access(cmd->args[0], X_OK) == -1)
		check_binaries(p, cmd);
	execve(cmd->args[0], cmd->args, p->env);
	free_struct(p);
	ft_exit("pipex: exec: Command not found\n", 127);
}
