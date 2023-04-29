/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:48:10 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/29 23:31:39 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_unclosed_quotes(char *str)
{
	int		i;
	t_bool	open_quotes;
	char	c;

	open_quotes = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			if (str[i + 1] != c)
				open_quotes = true;
			i++;
			while (str[i] && str[i] != c)
			{
				i++;
				if (str[i] && str[i] == c)
					open_quotes = false;
			}
		}
		i++;
	}
	return (open_quotes);
}

void	for_each_lex_node(t_lexer **list, void (*f)(t_lexer **cmd))
{
	t_lexer	*cur;
	t_lexer	*temp;

	cur = *list;
	while (cur)
	{
		temp = cur->next;
		f(&cur);
		cur = temp;
	}
}

void	lex_print_list(t_lexer *list)
{
	while (list)
	{
		printf("node: %s\n", list->data);
		list = list->next;
	}
}

void	free_lex(t_lexer **list)
{
	t_lexer	*c;

	c = *list;
	free(c->data);
	free(c);
}
