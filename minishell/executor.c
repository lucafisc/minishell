/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/07 18:24:30 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_pipe(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (true);
	return (false);
}

int		count_cmds(t_lexer *lex)
{
	int		n_cmds;

	n_cmds = 1;
	while (lex)
	{
		if (is_pipe(lex->data))
			n_cmds++;
		lex = lex->next;
		
	}
	return (n_cmds);
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
		// printf("start->data: %s\n", start->data);
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

t_command	*new_cmd_list_from_lex(t_lexer *lex, int n_cmds)
{
	t_command	*new;
	t_lexer		*start;
	int			len;
	int			i;

	i = 1;
	printf("n_cmds: %d\n", n_cmds);
	while (lex && i <= n_cmds)
	{
		len = 0;
		start = lex;
		while (lex && !is_pipe(lex->data))
		{
			len++;
			lex = lex->next;
		}
		if (i == 1)
		{
			new = new_cmd_node(start, len);
			// write(1, "here1\n", 6);
			// printf("index 0 of firs node: %s\n", new->cmd[0]);
			// write(1, "here2\n", 6);
		}
		else
			add_to_back_cmd(&new, new_cmd_node(start, len));
		i++;
		if (lex && lex->next)
			lex = lex->next;
	}
	return (new);
}

t_command	*simple_parser(t_lexer *lex)
{
	t_command	*cmd;
	int			n_cmds;

	n_cmds = count_cmds(lex);
	cmd = new_cmd_list_from_lex(lex, n_cmds);
	//write(1, "hello\n", 6);
	return (cmd);
}


void	free_command(t_command **cmd)
{
	int	i;
	t_command	*c;
	
	c = *cmd;
	i = 0;
	while (c->cmd[i])
	{
		// printf("free %s\n", c->cmd[i]);
		free(c->cmd[i]);
		i++;
	}
	free(c->cmd);
	free(c);
}

void	test_parser(t_lexer *lex)
{
	t_command	*cmds;
	t_command	*temp;

	cmds = simple_parser(lex);
	while (cmds)
	{
		printf("new node ____________\n");
		ft_print_strarr(cmds->cmd);
		temp = cmds;
		cmds = cmds->next;
		free_command(&temp);
	}

}


// void	execute(t_shell *s, t_lexer *lex)
// {
// 	t_command	*parsed_cmd;
// 	pid_t		pid;

// 	parsed_cmd = simple_parser(lex);
// 	find_cmd(s, parsed_cmd->cmd[0]);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		// printf("exec %s\n", parsed_cmd->cmd[0]);
// 		execve(parsed_cmd->cmd[0], parsed_cmd->cmd, s->env);
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(parsed_cmd->cmd[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 	}
// 	wait(NULL);
// 	free_command(parsed_cmd);
// }
