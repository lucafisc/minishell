/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/17 19:30:38 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_pipe(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (true);
	return (false);
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
		len = 0;
		start = lex;
		while (lex && !is_pipe(lex->data))
		{
			// printf("checking lex_data: %s ", lex->data);
			if (is_redir(lex->data))
			{
				// printf("is_redir\n");
				lex = lex->next;
				if (lex)
					lex->info = LEX_FILE;
			}
			else
			{
				len++;
				// printf("command is longer: %d\n", len);
			}
			if (lex)
			{
				lex = lex->next;
				// printf("moving to the next token: %s\n", lex ? lex->data:"empty");
			}
		}
		if (i == 1)
			new = par_list_new_node(start, len);
		else
			par_list_add_back(&new, par_list_new_node(start, len));
		i++;
		if (lex && lex->next)
			lex = lex->next;
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
	// printf("n_cmd: %d\n", n_cmds);
	return (cmd);
}
