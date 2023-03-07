/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross < lde-ross@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:16:35 by lde-ross          #+#    #+#             */
/*   Updated: 2023/02/01 17:57:21 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	init_status(t_status *stat)
{
	(*stat).client_pid = 0;
	(*stat).pid_received = false;
}

void	init_act(struct sigaction *act, void (*handler)(int))
{
	(*act).sa_handler = handler;
	sigemptyset(&act->sa_mask);
	(*act).sa_flags = 0;
}

t_bool	is_end_of_msg(int i)
{
	if (i == 255)
		return (true);
	else
		return (false);
}

void	print_pid(int pid)
{
	ft_printf(BMAG "\n            _       _   _        _ _    \n" COLOR_RESET);
	ft_printf(BMAG "           (_)     (_) | |      | | |   \n" COLOR_RESET);
	ft_printf(BMAG "  _ __ ___  _ _ __  _  | |_ __ _| | | __\n" COLOR_RESET);
	ft_printf(BMAG " | '_ ` _ \\| | '_ \\| | | __/ _` | | |/ /\n" COLOR_RESET);
	ft_printf(BMAG " | | | | | | | | | | | | || (_| | |   < \n" COLOR_RESET);
	ft_printf(BMAG " |_| |_| |_|_|_| |_|_|  \\__\\__,_|_|_|\\_\\\n" COLOR_RESET);
	ft_printf(BMAG "\n               ");
	ft_printf(HMAG " PID = %d ", pid, COLOR_RESET);
	ft_printf(COLOR_RESET "\n\n");
}
