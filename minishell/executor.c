/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/01 16:04:35 by lde-ross         ###   ########.fr       */
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
	if (command->script_line)
	{
		ft_putstr_fd("minishell: line ", 2);
		ft_putnbr_fd(command->script_line, 2);
		ft_error(NULL, command->cmd[0], "command not found", 127);
	}
	else
		ft_error("minishell", command->cmd[0],
			"command not found", 127);
	exit(1);
}

void	wait_for_child(int *pids, int n_children)
{
	int	i;

	i = n_children - 1;
	while (g_shell->status != 130 && waitpid(pids[i], NULL, WNOHANG) == 0)
	{
		if (g_shell->status == 130)
			kill(pids[i], SIGINT);
	}
	i--;
	while (i >= 0)
	{
		kill(pids[i], SIGINT);
		wait(&pids[i]);
		i--;
	}
	free(pids);
}

void	parent_routine(t_command **command)
{
	t_command	*tmp;
	t_command	*current;

	current = *command;
	tmp = current->next;
	printf("parent routine (cmd is %s). my outfile is %d and my infile is %d\n", current->cmd[0], current->outfile, current->infile);
	close_fd(current);
	unlink(HEREDOC_NAME);
	free_command(current);
	*command = tmp;
}

int		get_n_children(t_shell *s, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (!is_param(cmd->cmd[0]) && find_builtin(s, cmd->cmd[0]) == -1)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	execute(t_shell *s, t_command *parsed_cmd)
{
	int	builtin_idx;
	int	n_children;
	int	i;
	int	*pids;

	n_children = get_n_children(s, parsed_cmd);
	pids = malloc(sizeof(int) * n_children);
	i = 0;
	while (parsed_cmd)
	{
		builtin_idx = find_builtin(s, parsed_cmd->cmd[0]);
		if (is_param(parsed_cmd->cmd[0]))
			add_param(s, parsed_cmd);
		else if (builtin_idx >= 0)
			exec_builtin(s, parsed_cmd, builtin_idx);
		else
		{
			trim_cmd(&parsed_cmd);
			parsed_cmd->cmd[0] = find_cmd(s, parsed_cmd->cmd[0]);
			pids[i] = fork();
			g_shell->forked = true;
			if (pids[i] == 0)
				child_routine(s, parsed_cmd);
			i++;
		}
		parent_routine(&parsed_cmd);
	}
	wait_for_child(pids, n_children);
	//free(pids);
	g_shell->forked = false;
	add_status(g_shell->status);
	g_shell->status = 0;
}
