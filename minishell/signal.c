/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:34:05 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/24 14:51:38 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_shell	*g_shell;

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		g_shell->status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_shell->forked)
			rl_redisplay();
	}
	// else if (signal == SIGQUIT)
	// 	ft_putstr_fd("Handle SIQUIT\n", 1);
}

// void	init_act(struct sigaction *act, void (*handler)(int))
// {
// 	(*act).sa_handler = handler;
// 	sigemptyset(&act->sa_mask);
// 	(*act).sa_flags = 0;
// }

void	init_signal(void)
{
	// struct sigaction	act;

	// init_act(&act, &handler);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	//sigaction(SIGQUIT, &act, NULL);
}
