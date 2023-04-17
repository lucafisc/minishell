/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:34:05 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/17 14:20:17 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0); // clearing the current input line in the terminal.
		rl_on_new_line();
		printf("\n");
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
