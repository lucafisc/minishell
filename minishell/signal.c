/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:34:05 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/07 11:56:26 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		//ft_putstr_fd("Handle SIGINT\n", 1);
		//rl_replace_line("Hello", 0);
	}
	else if (signal == SIGQUIT)
		ft_putstr_fd("Handle SIQUIT\n", 1);
}

void	init_act(struct sigaction *act, void (*handler)(int))
{
	(*act).sa_handler = handler;
	sigemptyset(&act->sa_mask);
	(*act).sa_flags = 0;
}

void	init_signal(void)
{
	struct sigaction	act;

	init_act(&act, &handler);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
