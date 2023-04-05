/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:12:19 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/05 16:37:12 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	raw_tokens = ft_cmd_trim(fmt);
	list = new_lexer_list_from_matrix(raw_tokens);
	split_list(&list);
	return (list);
}

// t_lexer	*lexer(char *fmt)
// {
// 	t_lexer	*first;
// 	int	i;

// 	first = ft_dbllstnew(NULL, 0);
// 	i = 0;
// 	while (fmt[i])
// 	{
// 		if (fmt[i] == '|')
// 		{
// 			ft_dbllst_addback(first, ft_dbllstnew(NULL, 0));
// 			first = first->next;
// 		}
// 		else
// 			first->data = ft_joinnfree(first->data, fmt[i]);
// 		i++;
// 	}
// }
