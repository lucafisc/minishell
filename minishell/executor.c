/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor .c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/28 17:01:13 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_shell *s, t_command *cmd, int builtin_idx)
{
	s->builtins[builtin_idx].func (s, cmd);
}

void	child_routine(t_shell *s, t_command *command)
{
	create_redir(command);
	execve(command->cmd[0], command->cmd, s->env);
	ft_error("minishell", command->cmd[0],
		"command not found", 127);
	exit(1);
}

void	wait_for_child(int pid)
{
	while (g_shell->status != 130 && waitpid(pid, NULL, WNOHANG) == 0)
	{
		if (g_shell->status == 130)
			kill(pid, SIGINT);
	}
}

void	parent_routine(t_command **command)
{
	t_command	*tmp;
	t_command	*current;

	current = *command;
	tmp = current->next;
	close_fd(current);
	unlink(HEREDOC_NAME);
	free_command(current);
	*command = tmp;
}

void	execute(t_shell *s, t_command *parsed_cmd)
{
	pid_t		pid;
	int			builtin_idx;

	pid = -1;
	while (parsed_cmd)
	{
		builtin_idx = find_builtin(s, parsed_cmd->cmd[0]);
		if (is_param(parsed_cmd->cmd[0]))
			add_param(s, parsed_cmd);
		else if (builtin_idx >= 0)
			exec_builtin(s, parsed_cmd, builtin_idx);
		else
		{
			parsed_cmd->cmd[0] = find_cmd(s, parsed_cmd->cmd[0]);
			pid = fork();
			g_shell->forked = true;
			if (pid == 0)
				child_routine(s, parsed_cmd);
		}
		parent_routine(&parsed_cmd);
	}
	wait_for_child(pid);
	g_shell->forked = false;
	add_status(g_shell->status);
	g_shell->status = 0;
}
