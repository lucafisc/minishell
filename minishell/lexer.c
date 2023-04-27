/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:14:03 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 18:12:19 by lde-ross         ###   ########.fr       */
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
	raw_tokens = expander(raw_tokens);
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
