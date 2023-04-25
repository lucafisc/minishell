/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:48:10 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/25 21:35:13 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
