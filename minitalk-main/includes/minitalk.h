/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross < lde-ross@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:59:58 by lde-ross          #+#    #+#             */
/*   Updated: 2023/02/01 17:57:58 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_status {
	t_bool	pid_received;
	int		client_pid;
}	t_status;

extern t_status	g_status;

void	init_status(t_status *stat);
void	print_pid(int pid);
t_bool	is_end_of_msg(int i);
void	init_act(struct sigaction *act, void (*handler)(int));

#endif