/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:53:30 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/05 14:43:13 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char should_split(char *str)
{
	int i;

	i = 0;
	if (*str == '\'' || *str == '\"')
		return (0);
	while (SPLIT_CHAR[i])
	{
		if (ft_strchr(str, SPLIT_CHAR[i]))
			return (SPLIT_CHAR[i]);
		i++;
	}
	return (0);
}

t_lexer *new_lexer_list_from_matrix(char **matrix)
{
	t_lexer	*new;
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (i == 0)
			new = ft_dbllstnew(matrix[i], 1, i);
		else
			ft_dbllst_addback(&new, ft_dbllstnew(matrix[i], 1, i));
			i++;
	}
	return (new);
}

void	replace_node_by_list(t_lexer **list, t_lexer **node, t_lexer **new)
{
	t_lexer	*prev;
	t_lexer	*cur;
	t_lexer *nd;
	t_lexer	*x;

	cur = *new;
	nd = *list;
	x = *node;
	while (nd->index != x->index)
		nd = nd->next;
	if (nd->prev)
	{
		prev = nd->prev;
		prev->next = cur;	
		cur->prev = prev;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = nd->next;
	//free node!
	printf("replaced list\n");
	//printf("index: %d\n", nd->index);
	if (nd->index == 0 && !nd->next)
		*list = cur;
}

void	split_list(t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*new;
	char **matrix;
	char	c;

	cur = *list;
	while (cur)
	{
		if ((c = should_split(cur->data)) && cur->data[1])
		{
			matrix = ft_split_keep(cur->data, c);
			new = new_lexer_list_from_matrix(matrix);
			ft_free_str_arr(matrix);
			replace_node_by_list(list, &cur, &new);
			// print_list(&new);
			cur = *list;
		}
		cur = cur->next;
	}
	print_list(list);
	//printf("index: %d\n", cur->index);
}

void print_list(t_lexer **list)
{
	t_lexer *cur;
	int i;

	i = 1;
	cur = *list;
	while (cur)
	{
		printf("node %d:%s\n", i, cur->data);
		cur = cur->next;
		i++;
	}
}

// t_lexer *lexer_list(char **cmds)
// {



// 	return (list);
// }
