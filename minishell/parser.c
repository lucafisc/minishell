/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/11 18:44:02 by lde-ross         ###   ########.fr       */
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

void	for_each_cmd(t_command **cmd, void (*f)(t_command **cmd))
{
	t_command	*cur;

	cur = *cmd;
	while (cur)
	{
		f(&cur);
		cur = cur->next;
	}
}

t_bool	is_escapable(char c)
{
	if (!c)
		return (false);
	if (c == '\"' || c == '\'' || c == '|' || c == '<' || c == '>' || c == '\\')
		return (true);
	return (false);
}

int	get_len_trim_expand(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && !is_escaped(i, str))
			len--;
		else if (is_escapable(str[i]) && is_escaped(i, str))
			len--;
		len++;
		i++;
	}
	return (len);
}

char *trim_n_expand(char *str)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	len = get_len_trim_expand(str);
	new = ft_calloc(len, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && is_escapable(str[i + 1]))
			i++;
		else if ((str[i] == '\"' || str[i] == '\'') && !is_escaped(i, str))
			i++;
		new[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (new);
}

t_bool	has_quote_or_escaped(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_escapable(str[i]))
			return (true);
		i++;
	}
	return (false);
}

void	parse_trim_expand(t_command **cmd)
{
	t_command	*cur;
	int			i;

	cur = *cmd;
	i = 0;
	while (cur->cmd[i])
	{
		if (has_quote_or_escaped(cur->cmd[i]))
		{
			cur->cmd[i] = trim_n_expand(cur->cmd[i]);
		}
		i++;
	}
	
}

t_command	*parser(t_lexer *lex)
{
	t_command	*cmd;
	int			n_cmds;

	n_cmds = count_cmds(lex);
	cmd = new_cmd_list_from_lex(lex, n_cmds);
	for_each_cmd(&cmd, parse_trim_expand);
	return (cmd);
}

void	test_parser(t_lexer *lex)
{
	t_command	*cmds;
	t_command	*temp;

	cmds = parser(lex);
	while (cmds)
	{
		printf("\nnew node ____________\n");
		printf("outfile fd: %d\n", cmds->outfile);
		ft_print_strarr(cmds->cmd);
		temp = cmds;
		cmds = cmds->next;
		free_command(&temp);
	}
}
