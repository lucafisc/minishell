/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:53:30 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/11 18:08:36 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_chr_escaped(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c && !is_escaped(i, s))
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c && !is_escaped(i, s))
		return ((char *)&s[i]);
	return (0);
}

char should_split(char *str)
{
	int i;

	i = 0;
	if (*str == '\'' || *str == '\"' || !str[1])
		return (0);
	while (SPLIT_CHAR[i])
	{
		if (str_chr_escaped(str, SPLIT_CHAR[i]))
		{
			if (str[0] == SPLIT_CHAR[i] && str[1] == SPLIT_CHAR[i] && !str[2] && SPLIT_CHAR[i] != '|')
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
		fill_lexer_list(new_list, new->data, new->info, *i);
		new = new->next;
		*i += 1;
	}
}

t_lexer	*replace_node_by_list(t_lexer **list, t_lexer *node, t_lexer **to_insert)
{
	t_lexer	*new_list;
	t_lexer	*old;
	int		i;

	old = *list;
	i = 0;
	while (old)
	{
		if (old->index == node->index)
			fill_new_nodes_lexer(to_insert, &new_list, &i);
		else
		{
			fill_lexer_list(&new_list, old->data, old->info, i);
			i++;
		}
		old = old->next;
	}
	free_lexer_list(list);
	free_lexer_list(to_insert);
	return (new_list);
}

void	split_list(t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*new;
	char	**matrix;
	char	c;

	cur = *list;
	while (cur)
	{
		if ((c = should_split(cur->data)))
		{
			matrix = ft_split_keep(cur->data, c);
			new = new_lexer_list_from_matrix(matrix);
			ft_free_str_arr(matrix);
			*list = replace_node_by_list(list, cur, &new);
			cur = *list;
		}
		else
			cur = cur->next;
	}
}
