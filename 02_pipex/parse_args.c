/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:44:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/14 17:56:43 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Populates the commands in the structure with the commands given as
arguments
*/
void	get_args(t_pipe *p, char **av)
{
	int		i;

	if (p->here_doc)
	{
		get_heredoc_args(p, av);
		return ;
	}
	p->cmds = malloc (sizeof(t_cmd) * p->n_cmds);
	if (!p->cmds)
		ft_exit("pipex: Out of memory: get_args\n", 1);
	i = 0;
	while (i < p->n_cmds)
	{
		p->cmds[i].args = ft_split(av[i + 2], ' ');
		i++;
	}
}

t_cmd	*get_cmd(t_pipe *p, pid_t pid)
{
	int	i;

	i = 0;
	while (i < p->n_cmds)
	{
		if (p->process[i] == pid)
			return (&p->cmds[i]);
		i++;
	}
	return (NULL);
}

static void	find_cmd(t_pipe *p, t_cmd *cmd)
{
	int		i;
	char	*tmp_prog;

	i = 0;
	while (p->path[i])
	{
		tmp_prog = ft_strnjoin(3, p->path[i], "/", cmd->args[0]);
		if (access(tmp_prog, X_OK) != -1)
		{
			free(cmd->args[0]);
			cmd->args[0] = ft_strdup(tmp_prog);
			free(tmp_prog);
			break ;
		}
		free(tmp_prog);
		i++;
	}
}

void	check_binaries(t_pipe *p, t_cmd *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (p->env[i])
	{
		if (!ft_strncmp("PATH=", p->env[i], 5))
		{
			path = p->env[i];
			path += 5;
			p->path = ft_split(path, ':');
			find_cmd(p, cmd);
			ft_free_str_arr(p->path);
			break ;
		}
		i++;
	}
}
