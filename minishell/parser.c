/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/10 17:25:14 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_pipe(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (true);
	return (false);
}

int		count_cmds(t_lexer *lex)
{
	int		n_cmds;

	n_cmds = 1;
	while (lex)
	{
		if (is_pipe(lex->data))
			n_cmds++;
		lex = lex->next;
		
	}
	return (n_cmds);
}

t_command	*new_cmd_list_from_lex(t_lexer *lex, int n_cmds)
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
			if (is_redir(lex->data))
				lex = lex->next;
			else
				len++;
			if (lex)
				lex = lex->next;
		}
		if (i == 1)
			new = new_cmd_node(start, len);
		else
			add_to_back_cmd(&new, new_cmd_node(start, len));
		i++;
		printf("i was incremented now to %d\n", i);
		if (lex && lex->next)
			lex = lex->next;
	}
	return (new);
}

t_command	*parser(t_lexer *lex)
{
	t_command	*cmd;
	int			n_cmds;

	n_cmds = count_cmds(lex);
	cmd = new_cmd_list_from_lex(lex, n_cmds);
	return (cmd);
}

void	test_parser(t_lexer *lex)
{
	t_command	*cmds;
	t_command	*temp;

	cmds = parser(lex);
	while (cmds)
	{
		printf("new node ____________\n");
		printf("outfile fd: %d\n", cmds->outfile);
		//ft_print_strarr(cmds->cmd);
		temp = cmds;
		cmds = cmds->next;
		free_command(&temp);
	}
}
