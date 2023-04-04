/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:53:30 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/03 20:55:39 by lde-ross         ###   ########.fr       */
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

void	split_list(t_lexer **list)
{
	t_lexer *cur;
	char **matrix;
	char	c;
	int		i;

	cur = *list;
	while (cur)
	{
		if ((c = should_split(cur->data)) && cur->data[1])
		{
			printf("this is the split char: %c\n",c);
			matrix = ft_split_keep(cur->data, c);
			while (matrix[i])
			{
				/* code */
			}
			
			ft_print_strarr(matrix);
		}
		cur = cur->next;
	}
	
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
