/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/25 16:47:42 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	raw_tokens = lex_split_token(fmt);
	//ft_print_strarr(raw_tokens);
	list = lex_list_from_table(raw_tokens);
	ft_free_str_arr(raw_tokens);
	lex_split_list(&list);
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
	exit(1);
	// execute(s, list);
	return (list);
}
