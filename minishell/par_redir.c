/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:55:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/26 19:37:20 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		// throw_err("open", start->next->data);
		ft_error(new->cmd[0], strerror(errno), start->next->data, errno);
}

static void	read_stdin(t_lexer *lex, int heredoc_fd, char *line)
{
	int	len;

	while (1)
	{
		line = readline("minishell heredoc> ");
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 1 && !ft_strncmp(line, lex->data, len))
			break ;
		ft_putendl_fd(line, heredoc_fd);
		free(line);
	}
	free(line);
}

void	handle_heredoc(t_lexer *lex, int *open_flag)
{
	char	*line;
	int		heredoc_fd;

	line = NULL;
	heredoc_fd = open(HEREDOC_NAME, *open_flag, 0644);
	if (heredoc_fd < 0)
		throw_err("heredoc", NULL);
	read_stdin(lex, heredoc_fd, line);
	close(heredoc_fd);
	*open_flag = O_RDONLY;
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

void	new_redir(int redir, t_lexer **lexer_node, t_command **cmd_node)
{
	t_lexer	*start;

	start = *lexer_node;
	if (!start->next && redir)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
		start = start->next;
		return ;
	}
	if (redir == OUT_WRITE || redir == OUT_APPEND)
		open_out(redir, start, cmd_node);
	else
		open_in(redir, start, cmd_node);
	start = start->next;
}

void	par_fill_cmd(int *i, t_lexer *start, t_command **cmd_node)
{
	int			str_len;
	t_command	*new;

	new = *cmd_node;
	// printf("Filling node\n");
	str_len = ft_strlen(start->data);
	new->cmd[*i] = malloc(sizeof(char) * (str_len + 1));
	if (!new->cmd[*i])
		return ;
	ft_strlcpy(new->cmd[*i], start->data, str_len + 1);
	// printf("new cmd: %s\n", new->cmd[*i]);
	*i += 1;
}
