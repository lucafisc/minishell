/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/04 14:11:15 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexersize(t_lexer *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_command	*simple_parser(t_lexer *lex)
{
	t_command	*cmd;
	int			i;
	int			len;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = malloc(sizeof(char *) * (ft_lexersize(lex) + 1));
	if (!cmd->cmd)
		return (NULL);
	i = 0;
	while (lex)
	{
		len = ft_strlen(lex->data);
		cmd->cmd[i] = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(cmd->cmd[i], lex->data, len + 1);
		lex = lex->next;
		i++;
	}
	cmd->cmd[i] = NULL;
	// printf("EXECUTOR\n*************\n");
	// ft_print_strarr(cmd->cmd);
	return (cmd);
}

void	free_command(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->cmd[++i])
	{
		printf("free %s\n", cmd->cmd[i]);
		free(cmd->cmd[i]);
	}
	free(cmd);
}

void	execute(t_shell *s, t_lexer *lex)
{
	t_command	*parsed_cmd;
	pid_t		pid;

	parsed_cmd = simple_parser(lex);
	find_cmd(s, parsed_cmd->cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		printf("exec %s\n", parsed_cmd->cmd[0]);
		execve(parsed_cmd->cmd[0], parsed_cmd->cmd, s->env);
		throw_err("exec", parsed_cmd->cmd[0]);
	}
	free_command(parsed_cmd);
}
