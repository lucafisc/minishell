/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:58:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/03 17:56:28 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_shell *s, t_command *cmd, int builtin_idx)
{
	s->builtins[builtin_idx].func (s, cmd);
}

void	wait_for_child(int *pids, int n_children)
{
	int	i;

	if (n_children == 0)
	{
		free(pids);
		return ;
	}
	i = n_children - 1;
	while (g_shell->status != 130
		&& waitpid(pids[i], &g_shell->status, WNOHANG) == 0)
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

int	get_n_children(t_shell *s, t_command *cmd)
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

void	execute_routine(t_command **parsed_cmd, int **pids_p, int *i)
{
	int			builtin_idx;
	t_command	*cmd;
	t_command	*first;
	int			*pids;

	first = *parsed_cmd;
	cmd = *parsed_cmd;
	pids = *pids_p;
	builtin_idx = find_builtin(g_shell, cmd->cmd[0]);
	if (is_param(cmd->cmd[0]))
		add_param(g_shell, cmd);
	else if (builtin_idx >= 0)
		exec_builtin(g_shell, cmd, builtin_idx);
	else
	{
		cmd->cmd[0] = find_cmd(g_shell, cmd->cmd[0]);
		pids[*i] = fork();
		g_shell->forked = true;
		if (pids[*i] == 0)
			child_routine(g_shell, cmd, first);
		(*i)++;
	}
	parent_routine(parsed_cmd);
}

void	execute(t_shell *s, t_command *parsed_cmd)
{
	int	n_children;
	int	*pids;
	int	i;

	n_children = get_n_children(s, parsed_cmd);
	pids = malloc(sizeof(int) * n_children);
	if (!pids)
		return ;
	i = 0;
	while (parsed_cmd)
		execute_routine(&parsed_cmd, &pids, &i);
	wait_for_child(pids, n_children);
	g_shell->forked = false;
	add_status(g_shell->status);
	g_shell->status = 0;
}
