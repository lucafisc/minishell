/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/06 18:03:09 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexersize(t_lexer *lst)
{
	int	i;

	i = 0;
	while (lst && !ft_strncmp(lex->data, "|", 1) == 0)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int		count_cmds(t_lexer *lex)
{
	t_lexer	*lex;
	int		n_cmds;

	n_cmds = 1;
	while (lex)
	{
		if (ft_strncmp(lex->data, "|", 1) == 0)
			n_cmds++;
		lex = lex->next;
		
	}
	return (n_cmds);
}

void	fill_cmds_list(t_command **cmd, t_lexer *lex, int n_cmds)
{
	int	i;

	i = 1;
	while (i < n_cmds)
	{
		if (i == 1)
		{
			*cmds = 
			new = malloc(sizeof(*new));
		}
	}
	
}

t_command	**simple_parser(t_lexer *lex)
{
	t_command	*cmd;
	int			i;
	int			len;
	int			n_cmds;

	n_cmds = count_cmds(lex);
	fill_cmds_list(&cmd, lex, n_cmds);


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
		// printf("free %s\n", cmd->cmd[i]);
		free(cmd->cmd[i]);
	}
	free(cmd);
}

void	execute(t_shell *s, t_lexer *lex)
{
	t_command	**parsed_cmd;
	pid_t		pid;

	parsed_cmd = simple_parser(lex);
	find_cmd(s, parsed_cmd->cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		// printf("exec %s\n", parsed_cmd->cmd[0]);
		execve(parsed_cmd->cmd[0], parsed_cmd->cmd, s->env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parsed_cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	wait(NULL);
	free_command(parsed_cmd);
}
