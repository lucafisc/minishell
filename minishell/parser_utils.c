/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:56:16 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/11 14:55:19 by lde-ross         ###   ########.fr       */
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

void open_out(int redir, t_lexer *start, t_command **cmd_node)
{
	int open_flag;
	t_command *new;

	new = *cmd_node;
	if (redir == OUT_WRITE)
		open_flag = O_WRONLY;
	else
		open_flag = (O_WRONLY | O_APPEND);
	new->outfile = open(start->next->data, open_flag);
	if (new->outfile == -1)
		throw_err("open", start->next->data);
}

void open_in(int redir, t_lexer *start, t_command **cmd_node)
{
	int open_flag;
	t_command *new;

	new = *cmd_node;
	if (redir == IN_READ)
		open_flag = O_RDONLY;
	else
		open_flag = (O_RDWR | O_CREAT | O_APPEND);
	new->infile = open(start->next->data, open_flag);
	if (new->infile == -1)
		throw_err("open", start->next->data);
}

void new_redir(int redir, t_lexer **lexer_node, t_command **cmd_node)
{
	t_lexer *start;

	start = *lexer_node;
	if (!start->next && (redir == OUT_WRITE || redir == OUT_APPEND || redir == IN_READ)) // same also for HEREDOC?
	{
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
		start = start->next;
		return;
	}
	if (redir == OUT_WRITE || redir == OUT_APPEND)
		open_out(redir, start, cmd_node);
	else
		open_in(redir, start, cmd_node);
	start = start->next;
}

void fill_cmd(int *i, t_lexer *start, t_command **cmd_node)
{
	int str_len;
	t_command *new;

	new = *cmd_node;
	str_len = ft_strlen(start->data);
	new->cmd[*i] = malloc(sizeof(char) * (str_len + 1));
	if (!new->cmd[*i])
		return;
	ft_strlcpy(new->cmd[*i], start->data, str_len + 1);
	*i += 1;
}

t_command *new_cmd_node(t_lexer *start, int len)
{
	t_command *new;
	int i;
	int redir;

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
		redir = is_redir(start->data);
		if (redir)
			new_redir(redir, &start, &new);
		else if (i < len)
			fill_cmd(&i, start, &new);
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
	if (c->infile != -1)
		close(c->infile);
	if (c->outfile != -1)
		close(c->outfile);
	free(c->cmd);
	free(c);
}
