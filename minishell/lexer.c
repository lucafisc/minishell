/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/17 22:03:38 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	raw_tokens = lex_split_token(fmt);
	// ft_print_strarr(raw_tokens);
	list = lex_list_from_table(raw_tokens);
	ft_free_str_arr(raw_tokens);
	lex_split_list(&list);
	// while (list->data)
	// {
	// 	printf("%s\n", list->data);
	// 	list = list->next;
	// }
	// execute(s, list);
	return (list);
}
