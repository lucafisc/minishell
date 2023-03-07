/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:00:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 21:04:40 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "./libft/libft.h"

# define HEREDOC ".here_doc.tmp"

typedef struct s_cmd
{
	char	**args;
	int		fd_in;
	int		fd_out;
}				t_cmd;

typedef struct s_pipe
{
	int			n_cmds;
	t_cmd		*cmds;
	char		**env;
	char		*here_doc;
	pid_t		*process;
	char		**path;
}				t_pipe;

void	inherit_env(t_pipe *p, char **envp);
void	get_args(t_pipe *p, char **av);
void	create_commands(t_pipe *p, int ac, char **av);
void	close_parents(t_pipe *p);
void	check_binaries(t_pipe *p, t_cmd *cmd);
t_cmd	*get_cmd(t_pipe *p, pid_t pid);
void	ft_fork(t_pipe *p);
void	ft_exec_cmd(t_pipe *p, t_cmd *cmd);
void	close_fd(t_pipe *p);
void	free_struct(t_pipe *p);
void	free_invalid_file(t_pipe *p);

/* Error handling */
int		ft_error(char *name, char *desc);
void	ft_exit(const char *msg, int code);

/* Bonus */
void	get_heredoc_args(t_pipe *p, char **av);
void	handle_here_doc(t_pipe *p, char **av);

#endif
