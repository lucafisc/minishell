/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:12:19 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/28 18:17:20 by lde-ross         ###   ########.fr       */
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
	raw_tokens = ft_split(fmt, ' ');
	first = ft_dbllstnew(raw_tokens[i], i);
	while (raw_tokens[++i])
	{
		ft_dbllst_addback(&first, ft_dbllstnew(raw_tokens[i], i));
	}
	while (first)
	{
		printf("%d - %s\n", first->info, first->data);
		first = first->next;
	}
	return (first);
}

char	*ft_joinnfree(char *existing, char new)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!existing)
		existing = ft_calloc(1, sizeof(char));
	if (!new)
		return (NULL);
	new_str = ft_calloc((ft_strlen(existing) + 1 + 1), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (existing[++i])
		new_str[i] = existing[i];
	new_str[i] = new;
	free(existing);
	return (new_str);
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