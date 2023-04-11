/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/11 14:56:52 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	raw_tokens = ft_cmd_trim(fmt);
	printf("\nraw tokens\n");
	ft_print_strarr(raw_tokens);
	list = new_lexer_list_from_matrix(raw_tokens);
	ft_free_str_arr(raw_tokens);
	split_list(&list);
	printf("\nnodes before being parsed:\n");
	print_list(list);
	// execute(s, list);
	return (list);
}
