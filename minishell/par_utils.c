/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:56:16 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/13 17:34:19 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void for_each_par_node(t_command **cmd, void (*f)(t_command **cmd))
{
	t_command	*cur;
	t_command	*temp;

	cur = *cmd;
	while (cur)
	{
		temp = cur->next;
		f(&cur);
		cur = temp;
	}
}

void free_par(t_command **cmd)
{
	int i;
	t_command *c;

	c = *cmd;
	i = 0;
	while (c->cmd[i])
	{
		free(c->cmd[i]);
		printf("%d\n", i);
		i++;
	}
	if (c->infile != -1)
		close(c->infile);
	if (c->outfile != -1)
		close(c->outfile);
	free(c->cmd);
	free(c);
}
