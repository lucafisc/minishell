/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:53:30 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/02 18:25:20 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_chr_escaped(char *s, int c)
{
	int		i;
	char	quote;

	i = 0;
	quote = '0';
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && quote == '0')
			quote = s[i];
		else if (quote == s[i])
			quote = '0';
		else if (s[i] == (char)c && !ft_is_escaped(i, s) && quote == '0')
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c && !ft_is_escaped(i, s))
		return ((char *)&s[i]);
	return (0);
}

char	should_split(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0] || !str[1])
		return (0);
	while (SPLIT_CHAR[i])
	{
		if (str_chr_escaped(str, SPLIT_CHAR[i]))
		{
			if (str[0] == SPLIT_CHAR[i] && str[1] == SPLIT_CHAR[i] \
			&& !str[2] && SPLIT_CHAR[i] != '|')
				return (0);
			return (SPLIT_CHAR[i]);
		}
		i++;
	}
	return (0);
}

void	fill_new_nodes_lexer(t_lexer **to_insert, t_lexer **new_list, int *i)
{
	t_lexer	*new;

	new = *to_insert;
	while (new)
	{
		fill_lex_list(new_list, new->data, new->info, *i);
		new = new->next;
		*i += 1;
	}
}

t_lexer	*replace_node(t_lexer *cur, t_lexer *new, t_lexer **start)
{
	t_lexer	*end;

	new->prev = cur->prev;
	if (new->prev)
		new->prev->next = new;
	else
		*start = new;
	end = new;
	while (end->next)
		end = end->next;
	end->next = cur->next;
	if (end->next)
		end->next->prev = end;
	free(cur->data);
	free(cur);
	return (*start);
}

void	lex_split_list(t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*new;
	char	**matrix;
	char	c;

	cur = *list;
	while (cur)
	{
		c = should_split(cur->data);
		if (c)
		{
			matrix = ft_split_keep(cur->data, c);
			new = lex_list_from_table(matrix);
			ft_free_str_arr(matrix);
			cur = replace_node(cur, new, list);
		}
		else
			cur = cur->next;
	}
}
