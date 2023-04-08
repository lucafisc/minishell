/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:56:16 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/08 16:12:14 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_redir(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (true);
	return (false);
}

t_command	*new_cmd_node(t_lexer	*start, int len)
{
	t_command	*new;
	int			str_len;
	int			i;

	new = malloc(sizeof(*new));
	new->cmd = malloc(sizeof(*new->cmd) * (len + 1));
	if (!new->cmd)
		return (NULL);
	new->cmd[len] = NULL;
	new->prev = NULL;
	new->next = NULL;
	i = 0;
	while (i < len)
	{
		str_len = ft_strlen(start->data);
		new->cmd[i] = malloc(sizeof(char) * (str_len + 1));
		if (!new->cmd[i])
			return (NULL);
		ft_strlcpy(new->cmd[i], start->data, str_len + 1);
		i++;
		start = start->next;
	}
	return (new);
}

void	add_to_back_cmd(t_command **list, t_command *new)
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

void	free_command(t_command **cmd)
{
	int	i;
	t_command	*c;
	
	c = *cmd;
	i = 0;
	while (c->cmd[i])
	{
		free(c->cmd[i]);
		i++;
	}
	free(c->cmd);
	free(c);
}
