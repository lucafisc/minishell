/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross < lde-ross@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:17:34 by lde-ross          #+#    #+#             */
/*   Updated: 2023/02/02 16:36:40 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_status	g_status;

void	get_msg(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (00000001 << bit);
	bit++;
	if (bit == 8)
	{
		if (is_end_of_msg(i))
		{
			kill(g_status.client_pid, SIGUSR1);
			init_status(&g_status);
		}
		else
			write(1, &i, 1);
		bit = 0;
		i = 0;
	}
}

void	get_pid(int signal)
{
	static int	array[32];
	static int	i;

	if (i < 32)
	{
		if (signal == SIGUSR1)
			array[i] = 1;
		else
			array[i] = 0;
		i++;
	}
	if (i == 32)
	{
		g_status.client_pid = ft_bintoi(array);
		g_status.pid_received = true;
		i = 0;
	}
}

void	handler(int signal)
{
	if (!g_status.pid_received)
		get_pid(signal);
	else
		get_msg(signal);
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	if (argc != 1)
	{
		ft_printf(BRED " ✖ Error\n" COLOR_RESET);
		ft_printf(BYEL " 💡 Try $>%s\n", argv[0], COLOR_RESET);
		return (1);
	}
	init_status(&g_status);
	init_act(&act, &handler);
	print_pid(getpid());
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGUSR1, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
