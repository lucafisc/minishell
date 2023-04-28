/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:55:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/28 20:41:47 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	par_fill_cmd(int *i, t_lexer *start, t_command **cmd_node)
{
	// int			str_len;
	t_command	*new;

	new = *cmd_node;
	// str_len = ft_strlen(start->data);
	new->cmd[*i] = ft_strdup(start->data);
	// new->cmd[*i] = malloc(sizeof(char) * (str_len + 1));
	// if (!new->cmd[*i])
	// 	return ;
	// ft_strlcpy(new->cmd[*i], start->data, str_len + 1);
	*i += 1;
}
