/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/08 17:03:05 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */



#include "minishell.h"

// t_lexer	*ft_dbllstnew(char *data, int info)
// {
// 	t_lexer	*new;

// 	new = malloc(sizeof(*new));
// 	if (!new)
// 		return (NULL);
// 	new->data = ft_strdup(data);
// 	new->info = info;
// 	new->pipe = 0;
// 	new->prev = NULL;
// 	new->next = NULL;
// 	return (new);
// }

// void	ft_dbllst_addback(t_lexer **list, t_lexer *new)
// {
// 	t_lexer	*cur;

// 	if (!new)
// 		return ;
// 	cur = *list;
// 	while (cur->next)
// 		cur = cur->next;
// 	cur->next = new;
// 	new->prev = cur;
// 	new->next = NULL;
// }

t_lexer	*lexer(char *fmt)
{
	t_lexer	*list;
	char	**raw_tokens;

	raw_tokens = ft_cmd_trim(fmt);
	list = new_lexer_list_from_matrix(raw_tokens);
	ft_free_str_arr(raw_tokens);
	split_list(&list);
	//execute(s, list);
	return (list);
}

