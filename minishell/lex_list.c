/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:56:58 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/27 20:50:49 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* passing the trimmed version of the node */
t_lexer	*lex_list_new_node(char *data, int info)
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
		// if (i > 0 && ft_strncmp(matrix[i - 1], "echo", 5))
		// matrix[i] = trim_quotes(matrix[i]);
		i++;
	}
	return (new);
}
