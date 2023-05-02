/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:16:56 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/02 15:34:27 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	close_extra_fds(t_command *command, t_command *first)
{
	while (first)
	{
		if (first->infile != command->infile)
			close(first->infile);
		if (first->outfile != command->outfile)
			close(first->outfile);
		first = first->next;
	}
	
}


void	child_routine(t_shell *s, t_command *command, t_command *first)
{
	printf("command: %s outfile: %d infile: %d\n", command->cmd[0], command->outfile, command->infile);
	close_extra_fds(first, command);
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
