/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:54:04 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/17 19:26:48 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*par_list_new_node(t_lexer *start, int len)
{
	t_command	*new;
	int			i;
	int			redir;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->cmd = ft_calloc((len + 1), sizeof(*new->cmd));
	if (!new->cmd)
		return (NULL);
	new->infile = -1;
	new->outfile = -1;
	new->prev = NULL;
	new->next = NULL;
	i = 0;
	while (start)
	{
		// printf("new node. checking %s\n", start->data);
		// printf("attributes: info %d pipe %d\n", start->info, start->pipe);
		redir = is_redir(start->data);
		if (redir)
			new_redir(redir, &start, &new);
		else if (i < len && start->info != LEX_FILE)
			par_fill_cmd(&i, start, &new);
		start = start->next;
	}
	return (new);
}

void	par_list_add_back(t_command **list, t_command *new)
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
