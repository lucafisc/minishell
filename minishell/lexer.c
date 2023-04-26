/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/26 02:14:23 by tfregni          ###   ########.fr       */
=======
/*   Updated: 2023/04/23 22:39:59 by tfregni          ###   ########.fr       */
>>>>>>> tim
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	raw_tokens = lex_split_token(fmt);
<<<<<<< HEAD
	//ft_print_strarr(raw_tokens);
	list = lex_list_from_table(raw_tokens);
	ft_free_str_arr(raw_tokens);
	lex_split_list(&list);
	// while (list)
	// {
	// 	printf("%s\n", list->data);
	// 	list = list->next;
	// }
	// execute(s, list);
=======
	list = lex_list_from_table(raw_tokens);
	ft_free_str_arr(raw_tokens);
	lex_split_list(&list);
>>>>>>> tim
	return (list);
}
