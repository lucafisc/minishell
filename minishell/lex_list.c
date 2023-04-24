/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:56:58 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/24 18:55:04 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lex_list_new_node(char *data, int info)
{
	t_lexer	*new;
	char	*tmp;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (is_redir(data))
	{
		tmp = ft_strtrim(data, " ");
		printf("data: %s$ tmp: %s$\n", data, tmp);
		// free(data);
		data = tmp;
	}
	new->data = ft_strdup(data);
	new->info = info;
	new->pipe = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	lex_list_add_back(t_lexer **list, t_lexer *new)
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

void	fill_lex_list(t_lexer **node, char *data, int info, int i)
{
	if (i == 0)
		*node = lex_list_new_node(data, info);
	else
		lex_list_add_back(node, lex_list_new_node(data, info));
}

t_lexer	*lex_list_from_table(char **matrix)
{
	t_lexer	*new;
	int		i;

	i = 0;
	while (matrix[i])
	{
		fill_lex_list(&new, matrix[i], LEX_CMD, i);
		i++;
	}
	return (new);
}
