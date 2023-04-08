/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:56:16 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/08 19:42:31 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir is_redir(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0)
		return (OUT_WRITE);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (IN_READ);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (OUT_APPEND);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (HEREDOC);
	return (0);
}

t_command *new_cmd_node(t_lexer *start, int len)
{
	t_command *new;
	int str_len;
	int i;
	int redir;
	int open_flag;

	new = malloc(sizeof(*new));
	new->cmd = malloc(sizeof(*new->cmd) * (len + 1));
	if (!new->cmd)
		return (NULL);
	new->cmd[len] = NULL;
	new->infile = -1;
	new->outfile = -1;
	new->prev = NULL;
	new->next = NULL;
	i = 0;
	printf("len of cmd is: %d\n", len);
	while (start)
	{
		redir = is_redir(start->data);
		if (redir)
		{
			if (redir == OUT_WRITE || redir == OUT_APPEND)
			{
				if (redir == OUT_WRITE)
					open_flag = O_WRONLY;
				else if (redir == OUT_APPEND)
					open_flag = (O_WRONLY | O_APPEND);
				if (!start->next)
				{
					ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
					start = start->next;
					continue ;
				}
				new->outfile = open(start->next->data, open_flag);
				if (new->outfile == -1)
					throw_err("open", start->next->data);
			}
			else
			{
				if (redir == IN_READ)
					open_flag = O_RDONLY;
				else
					open_flag = (O_RDWR | O_CREAT | O_APPEND);
				new->infile = open(start->next->data, open_flag);
				if (new->infile == -1)
					throw_err("open", start->next->data);
			}
			start = start->next;

		}
		else
		{
			str_len = ft_strlen(start->data);
			new->cmd[i] = malloc(sizeof(char) * (str_len + 1));
			if (!new->cmd[i])
				return (NULL);
			ft_strlcpy(new->cmd[i], start->data, str_len + 1);
			i++;
		}
		start = start->next;
	}
	return (new);
}

void add_to_back_cmd(t_command **list, t_command *new)
{
	t_command *cur;

	if (!new)
		return;
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	new->next = NULL;
}

void free_command(t_command **cmd)
{
	int i;
	t_command *c;

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
