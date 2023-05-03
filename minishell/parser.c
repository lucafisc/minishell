/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/03 17:41:48 by lde-ross         ###   ########.fr       */
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
		if (pipe(fd_p) == -1)
			ft_error("minishell", "could not setup the pipe", "pipe", 1);
		if (cmd->outfile != 1)
			close(cmd->outfile);
		if (cmd->next->infile != 0)
			close(cmd->infile);
		cmd->outfile = fd_p[1];
		cmd->next->infile = fd_p[0];
		if (cmd->next)
			cmd = cmd->next;
	}
}

t_command	*par_list_from_lex(t_lexer *lex, int n_cmds)
{
	t_command	*new;
	t_lexer		*start;
	int			len;
	int			i;

	i = 1;
	while (lex && i <= n_cmds)
	{
		start = lex;
		len = get_node_len(&lex);
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
	free_lex_list(&lex);
	if (g_shell->pipe)
		setup_pipe(cmd, n_cmds);
	return (cmd);
}
