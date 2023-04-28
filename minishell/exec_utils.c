/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:49:58 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/28 21:05:22 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd)
{
	ft_free_str_arr(cmd->cmd);
	free(cmd);
}

void	close_fd(t_command *cmd)
{
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
}

void	create_redir(t_command *cmd)
{
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, 0) == -1)
		{
			ft_error("minishell", strerror(errno), "redirection", errno);
			exit(1);
		}
	}
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, 1) == -1)
		{
			ft_error("minishell", strerror(errno), "redirection", errno);
			exit(1);
		}
	}
}

/* Checks if the cmd is a builtin and in that case
returns its index number. Returns -1 if no match */
int	find_builtin(t_shell *s, char *cmd)
{
	int	i;
	int	len;

	if (!cmd || !cmd[0])
		return (-1);
	i = 0;
	len = ft_strlen(cmd);
	while (s->builtins[i].name)
	{
		if (!ft_strncmp(s->builtins[i].name, cmd, len)
			&& len == (int)ft_strlen(s->builtins[i].name))
			return (i);
		i++;
	}
	return (-1);
}

void	add_param(t_shell *s, t_command *c)
{
	char		*trimmed;

	trimmed = trim_quotes(c->cmd[0]);
	// free(c->cmd[0]);
	// c->cmd[0] = trimmed;
	s->params = env_append(s->params, trimmed);
}
