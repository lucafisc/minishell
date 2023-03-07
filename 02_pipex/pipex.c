/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:55:28 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 21:20:02 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->n_cmds)
	{
		if (p->cmds[i].fd_in != 0)
			close(p->cmds[i].fd_out);
		if (p->cmds[i].fd_out != 1)
			close(p->cmds[i].fd_in);
		i++;
	}
}

void	free_invalid_file(t_pipe *p)
{
	int	i;

	i = 0;
	if (p->cmds)
	{
		close(p->cmds[p->n_cmds - 1].fd_out);
		while (i < p->n_cmds)
		{
			if (p->cmds[i].args)
				ft_free_str_arr(p->cmds[i].args);
			i++;
		}
		free(p->cmds);
		p->cmds = NULL;
	}
	ft_free_str_arr(p->env);
	if (p->here_doc)
		unlink(HEREDOC);
	free(p->here_doc);
	free(p);
	exit (1);
}

void	free_struct(t_pipe *p)
{
	int	i;

	i = 0;
	if (p->cmds)
	{
		while (i < p->n_cmds)
		{
			if (p->cmds[i].fd_in != 0 && p->cmds[i].fd_in != 1)
				close(p->cmds[i].fd_out);
			if (p->cmds[i].fd_out != 1 && p->cmds[i].fd_out != 0)
				close(p->cmds[i].fd_out);
			if (p->cmds[i].args)
				ft_free_str_arr(p->cmds[i].args);
			i++;
		}
		free(p->cmds);
		p->cmds = NULL;
	}
	free(p->process);
	ft_free_str_arr(p->env);
	if (p->here_doc)
		unlink(HEREDOC);
	free(p->here_doc);
	free(p);
}

static void	check_args(int ac, char **av, t_pipe *p)
{
	if (av[1] && !ft_strcmp(av[1], "here_doc"))
	{
		if (ac < 5)
		{
			free(p);
			ft_exit("pipex: Usage: ./pipex here_doc infile cmd1 cmd2 \
			outfile\n", 1);
		}
		p->here_doc = ft_strjoin(av[2], "\n");
	}
	if (ac < 4)
	{
		free(p);
		ft_exit("pipex: Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 1);
	}
}

/*
Inherit environment
Get arguments
Create commands
Fork processes
Close parents
Free
*/
int	main(int ac, char **av, char **env)
{
	t_pipe	*p;

	p = malloc(sizeof(*p));
	if (!p)
		ft_exit("pipex: Out of memory: main\n", 1);
	p->here_doc = NULL;
	check_args(ac, av, p);
	p->n_cmds = ac - 3;
	inherit_env(p, env);
	get_args(p, av);
	create_commands(p, ac, av);
	p->process = malloc(sizeof(*p->process) * p->n_cmds);
	if (!p->process)
		ft_exit("pipex: Out of memory: process\n", 1);
	ft_fork(p);
	close_parents(p);
	free_struct(p);
}
