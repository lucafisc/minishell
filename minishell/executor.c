/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/23 15:44:25 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

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
	return (cmd);
}

void	free_command(t_command *cmd)
{
	ft_free_str_arr(cmd->cmd);
	free(cmd);
}

/* Checks if the cmd is a builtin and in that case
returns its index number. Returns -1 if no match */
int	find_builtin(t_shell *s, char *cmd)
{
	int	i;
	int	len;

	if (!cmd || !cmd[0])
		return (-1);
	i = 0;
	len = ft_strlen(cmd);
	while (s->builtins[i].name)
	{
		if (!ft_strncmp(s->builtins[i].name, cmd, len))
			return (i);
		i++;
	}
	return (-1);
}

// void	exec_builtin(t_shell *s, t_command *cmd, int builtin_idx)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		s->builtins[builtin_idx].func (s, cmd);
// 		exit(0);
// 	}
// }

void	create_redir(t_command *cmd)
{
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, 0) == -1)
		{
			throw_err("redirection", NULL);
			exit(1);
		}
	}
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, 1) == -1)
		{
			throw_err("redirection", NULL);
			exit(1);
		}
	}
}

void	exec_builtin(t_shell *s, t_command *cmd, int builtin_idx)
{
	s->builtins[builtin_idx].func (s, cmd);
}

void	close_fd(t_command *cmd)
{
	if (cmd->infile != 0)
	{
		// printf("Closing file descriptor %d\n", cmd->infile);
		close(cmd->infile);
	}
	if (cmd->outfile != 1)
	{
		// printf("Closing file descriptor %d\n", cmd->outfile);
		close(cmd->outfile);
	}
}

void	execute(t_shell *s, t_command *parsed_cmd)
{
	pid_t		pid;
	int			builtin_idx;
	int			status;
	t_command	*tmp;

	while (parsed_cmd)
	{
		builtin_idx = find_builtin(s, parsed_cmd->cmd[0]);
		if (builtin_idx >= 0)
			exec_builtin(s, parsed_cmd, builtin_idx);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				create_redir(parsed_cmd);
				parsed_cmd->cmd[0] = find_cmd(s, parsed_cmd->cmd[0]);
				execve(parsed_cmd->cmd[0], parsed_cmd->cmd, s->env);
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(parsed_cmd->cmd[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				exit(1);
			}
		}
		while (g_shell->status != 130 && waitpid(pid, &status, WNOHANG) == 0)
		{
			if (g_shell->status == 130)
			{
				printf("killing child\n");
				kill(pid, SIGINT);
			}
		}
		g_shell->status = 0;
		tmp = parsed_cmd->next;
		close_fd(parsed_cmd);
		free_command(parsed_cmd);
		parsed_cmd = tmp;
	}
}
