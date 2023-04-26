/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/26 20:13:25 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	if (has_unclosed_quotes(fmt))
	{
		ft_error("minishell", NULL, "unclosed quotes", 2);
		return (NULL);
	}
	raw_tokens = lex_split_token(fmt);
	if (!raw_tokens[0])
	{
		free(raw_tokens);
		return (NULL);
	}
	list = lex_list_from_table(raw_tokens);
	ft_free_str_arr(raw_tokens);
	lex_split_list(&list);
	return (list);
}
