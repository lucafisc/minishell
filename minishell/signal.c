/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:34:05 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 16:51:28 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

void	init_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
