/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:53:30 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/04 10:28:31 by lde-ross         ###   ########.fr       */
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
	t_lexer	*cur;
	t_lexer	*new;
	t_lexer	*temp;
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
			i = 0;
			while (matrix[i])
			{
				if (i == 0)
					new = ft_dbllstnew(matrix[i], 1);
				else
					ft_dbllstnew(&new, ft_dbllstnew(matrix[i], 1));
			}
			//ft_print_strarr(matrix);
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
