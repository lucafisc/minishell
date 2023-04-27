/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:54:04 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 17:04:56 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*init_command(int len)
{
	t_command	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->cmd = ft_calloc((len + 1), sizeof(*new->cmd));
	if (!new->cmd)
		return (NULL);
	new->infile = 0;
	new->outfile = 1;
	new->fd_pipe[0] = 0;
	new->fd_pipe[1] = 1;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_command	*par_list_new_node(t_lexer *start, int len)
{
	t_command	*new;
	int			i;
	int			redir;

	new = init_command(len);
	if (!new)
		return (NULL);
	i = 0;
	while (start)
	{
		redir = is_redir(start->data);
		if (redir)
			new_redir(redir, &start, &new);
		else if (i < len && start->info == LEX_CMD)
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
