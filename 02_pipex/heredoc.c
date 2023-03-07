/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:35:34 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 20:20:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_heredoc_args(t_pipe *p, char **av)
{
	int	i;

	p->n_cmds--;
	p->cmds = malloc (sizeof(t_cmd) * p->n_cmds);
	if (!p->cmds)
		ft_exit("pipex: Out of memory: get_heredoc_args\n", 1);
	i = 0;
	while (i < p->n_cmds)
	{
		p->cmds[i].args = ft_split(av[i + 3], ' ');
		i++;
	}
}

static void	read_stdin(t_pipe *p, int heredoc_fd, char *line)
{
	int	len;

	while (1)
	{
		write(1, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 1 && !ft_strncmp(line, p->here_doc, len))
			break ;
		write(heredoc_fd, line, len);
		free(line);
	}
	free(line);
}

void	handle_here_doc(t_pipe *p, char **av)
{
	char	*line;
	int		heredoc_fd;

	line = NULL;
	heredoc_fd = open(HEREDOC, O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
	if (heredoc_fd < 0)
		ft_error("here_doc", strerror(errno));
	read_stdin(p, heredoc_fd, line);
	close(heredoc_fd);
	p->cmds[0].fd_in = open(HEREDOC, O_RDONLY);
	if (p->cmds[0].fd_in < 0)
	{
		unlink(HEREDOC);
		ft_error("here_doc", strerror(errno));
	}
	p->cmds[0].fd_out = open(av[4], \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (p->cmds[p->n_cmds - 1].fd_out < 0)
		ft_error(av[4], strerror(errno));
}
