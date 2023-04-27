/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:54 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/27 16:20:00 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell	*g_shell;

t_bool is_pipe(char *str)
{
	if (str && *str && ft_strncmp(str, "|", 1) == 0)
		return (true);
	return (false);
}

void setup_pipe(t_command *cmd, int n_cmds)
{
	int fd_p[2];
	int i;

	i = -1;
	while (++i < n_cmds - 1)
	{
		if (pipe(fd_p) == -1)
			throw_err("minishell", "pipe");
		cmd->outfile = fd_p[1];
		cmd->next->infile = fd_p[0];
		cmd = cmd->next;
	}
}

int get_node_len(t_lexer **lex)
{
	int		len;
	t_lexer	*current;

	len = 0;
	current = *lex;
	while (current && !is_pipe(current->data))
	{
		if (is_redir(current->data))
		{
			current = current->next;
			if (current)
				current->info = LEX_FILE;
		}
		else
			len++;
		if (current)
			current = current->next;
	}
	*lex = current;
	return (len);
}

t_command *par_list_from_lex(t_lexer *lex, int n_cmds)
{
	t_command *new;
	t_lexer *start;
	int len;
	int i;

	i = 1;
	while (lex && i <= n_cmds)
	{
		start = lex;
		len = get_node_len(&lex);
		if (i == 1)
			new = par_list_new_node(start, len);
		else
			par_list_add_back(&new, par_list_new_node(start, len));
		i++;
		if (lex)
		{
			g_shell->pipe = true;
			lex = lex->next;
		}
	}
	return (new);
}

int par_count_cmds(t_lexer *lex)
{
	int n_cmds;

	n_cmds = 1;
	while (lex)
	{
		if (is_pipe(lex->data))
			n_cmds++;
		lex = lex->next;
	}
	return (n_cmds);
}

void free_lex_list(t_lexer **lex)
{
	t_lexer *tmp;

	while (*lex)
	{
		tmp = (*lex)->next;
		free((*lex)->data);
		free(*lex);
		*lex = tmp;
	}
}

void print_cmd_node(t_command **cmd)
{
	t_command *c;

	c = *cmd;
	ft_print_strarr(c->cmd);
}

void trim_cmd(t_command **cmd)
{
	int i;
	char *temp;
	t_command *command;

	i = 0;
	command = *cmd;
	while (command->cmd[i])
	{
		temp = trim_quotes(command->cmd[i]);
		free(command->cmd[i]);
		command->cmd[i] = temp;
		i++;
	}
}

t_command *parser(t_lexer *lex)
{
	t_command *cmd;
	int n_cmds;

	n_cmds = par_count_cmds(lex);
	cmd = par_list_from_lex(lex, n_cmds);
	free_lex_list(&lex);
	for_each_par_node(&cmd, trim_cmd);
	if (g_shell->pipe)
		setup_pipe(cmd, n_cmds);
	// printf("n_cmd: %d\n", n_cmds);
	return (cmd);
}
