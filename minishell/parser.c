/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/20 00:15:07 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_pipe(char *str)
{
	if (str && *str && ft_strncmp(str, "|", 1) == 0)
		return (true);
	return (false);
}

void	setup_pipe(t_command *cmd, int n_cmds)
{
	int	fd_p[2];
	int	i;

	i = -1;
	while (++i < n_cmds - 1)
	{
		// printf("PIPE #%d n_cmds: %d cmd: %s\n", i, n_cmds, cmd->cmd[0]);
		if (pipe(fd_p) == -1)
			throw_err("minishell", "pipe");
		cmd->outfile = fd_p[1];
		cmd->next->infile = fd_p[0];
		cmd = cmd->next;
	}
}

t_command	*par_list_from_lex(t_lexer *lex, int n_cmds)
{
	t_command		*new;
	t_lexer			*start;
	int				len;
	int				i;

	i = 1;
	while (lex && i <= n_cmds)
	{
		len = 0;
		start = lex;
		while (lex && !is_pipe(lex->data))
		{
			if (is_redir(lex->data))
			{
				lex = lex->next;
				if (lex)
					lex->info = LEX_FILE;
			}
			else
				len++;
			if (lex)
				lex = lex->next;
		}
		if (i == 1)
			new = par_list_new_node(start, len);
		else
			par_list_add_back(&new, par_list_new_node(start, len));
		i++;
		if (lex)
		{
			g_shell->pipe = true;
			lex = lex->next;
		}
	}
	return (new);
}

int	par_count_cmds(t_lexer *lex)
{
	int	n_cmds;

	n_cmds = 1;
	while (lex)
	{
		if (is_pipe(lex->data))
			n_cmds++;
		lex = lex->next;
	}
	return (n_cmds);
}

t_command	*parser(t_lexer *lex)
{
	t_command	*cmd;
	int			n_cmds;

	n_cmds = par_count_cmds(lex);
	cmd = par_list_from_lex(lex, n_cmds);
	for_each_par_node(&cmd, par_trim_expand);
	if (g_shell->pipe)
		setup_pipe(cmd, n_cmds);
	// printf("n_cmd: %d\n", n_cmds);
	return (cmd);
}
