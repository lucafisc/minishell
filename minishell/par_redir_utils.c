/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:56:58 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/01 17:41:32 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_out(int redir, t_lexer *start, t_command **cmd_node)
{
	int			open_flag;
	t_command	*new;

	new = *cmd_node;
	if (redir == OUT_WRITE)
		open_flag = (O_WRONLY | O_CREAT | O_TRUNC);
	else
		open_flag = (O_WRONLY | O_CREAT | O_APPEND);
	new->outfile = open(start->next->data, open_flag, 0644);
	if (new->outfile == -1)
		ft_error(new->cmd[0], strerror(errno), start->next->data, 1);
}

/* If start->next == NULL we got a problem (should go to stdin or stdout) */
void	open_in(int redir, t_lexer *start, t_command **cmd_node)
{
	int			open_flag;
	t_command	*new;

	new = *cmd_node;
	if (redir == IN_READ)
		open_flag = O_RDONLY;
	else
	{
		open_flag = (O_RDWR | O_CREAT | O_TRUNC | O_APPEND);
		start->next->info = LEX_TERM;
		handle_heredoc(start->next, &open_flag);
	}
	if (start->next->info == LEX_TERM)
	{
		new->infile = open(HEREDOC_NAME, open_flag, 0644);
		if (new->infile < 0)
			unlink(HEREDOC_NAME);
	}
	else
		new->infile = open(start->next->data, open_flag);
	if (new->infile == -1)
		ft_error(new->cmd[0], strerror(errno), start->next->data, 1);
}

t_redir	is_redir(char *str)
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

void	new_redir(int redir, t_lexer **lexer_node, t_command **cmd_node)
{
	t_lexer	*start;
	char	*err;

	err = "minishell: syntax error near unexpected token 'newline'\n";
	start = *lexer_node;
	if (!start->next && redir)
	{
		ft_putstr_fd(err, 2);
		start = start->next;
		return ;
	}
	if (redir == OUT_WRITE || redir == OUT_APPEND)
		open_out(redir, start, cmd_node);
	else
		open_in(redir, start, cmd_node);
	start = start->next;
}
