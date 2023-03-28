/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/28 17:10:34 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* returns a node, the cmd list is already allocated and 0-term */
t_command	*ft_dbllstnew(int len)
{
	t_command	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->cmd = malloc(sizeof(*new->cmd) * (len + 1));
	if (!new->cmd)
		return (NULL);
	new->cmd[len] = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_dbllst_addback(t_command **list, t_command *new)
{
	t_command	*cur;

	if (!new)
		return ;
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	new->next = NULL;
}

t_command	*parser(t_lexer *lexer)
{
	int	len;

	while (lexer)
	{
		len = 0;
		/* inner loop to check for the pipe */
		while (!lexer->pipe && lexer)
		{

			len++;
			lexer = lexer->next;
		}
		lexer = lexer->next;
	}
}
