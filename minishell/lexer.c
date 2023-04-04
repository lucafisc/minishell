/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:12:19 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/03 19:20:02 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_dbllstnew(char *data, int info)
{
	t_lexer	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = ft_strdup(data);
	new->info = info;
	new->pipe = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_dbllst_addback(t_lexer **list, t_lexer *new)
{
	t_lexer	*cur;

	if (!new)
		return ;
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	new->next = NULL;
}

t_lexer	*lexer(char *fmt)
{
	t_lexer	*first;
	char	**raw_tokens;
	int		i;

	i = 0;
	// raw_tokens = ft_split(fmt, ' ');
	raw_tokens = ft_cmd_trim(fmt);
	first = ft_dbllstnew(raw_tokens[i], i);
	while (raw_tokens[++i])
	{
		ft_dbllst_addback(&first, ft_dbllstnew(raw_tokens[i], i));
	}
	// while (first)
	// {
	// 	printf("%d - %s\n", first->info, first->data);
	// 	first = first->next;
	// }
	print_list(&first);
	split_list(&first);
	return (first);
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
