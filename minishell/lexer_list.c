/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:53:30 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/03 17:11:29 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *ft_dbllstnew(char *data, int info)
{
	t_lexer *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = ft_strdup(data);
	new->info = info;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void ft_dbllst_addback(t_lexer **list, t_lexer *new)
{
	t_lexer *cur;

	if (!new)
		return;
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	new->next = NULL;
}

t_bool *should_split(char *str)
{
	int i;
	char *c;

	i = 0;
	if (*str == '\'' || *str == '\"')
		return (false);
	while (SPLIT_CHAR[i])
	{
		if (ft_strchr(str, SPLIT_CHAR[i]))
			return (true);
		i++;
	}
	return (false);
}

void	split_list(t_lexer **list)
{
	t_lexer *cur;

	cur = *list;
	while (*cur)
	{
		if (should_split(cur->data))
		{
			
		}
		cur = cur->next;
	}
	
}

void print_list(t_lexer **list)
{
	t_lexer *cur;
	int i;

	i = 1;
	cur = *list;
	while (cur)
	{
		printf("node %d:%s\n", i, cur->data);
		cur = cur->next;
		i++;
	}
}

t_lexer *lexer_list(char **cmds)
{
	int i;
	t_lexer *list;

	i = 0;
	while (cmds[i])
	{
		if (i == 0)
			list = ft_dbllstnew(cmds[i], 1);
		else
			ft_dbllst_addback(&list, ft_dbllstnew(cmds[i], 1));
		i++;
	}
	return (list);
}
