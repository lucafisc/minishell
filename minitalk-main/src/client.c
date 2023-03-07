/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross < lde-ross@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:19:23 by lde-ross          #+#    #+#             */
/*   Updated: 2023/02/02 16:53:17 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_msg(int pid, char c)
{
	int	x;

	x = 1;
	while (x <= 128)
	{
		if (c & x)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		x = x << 1;
	}
}

void	send_pid(int pid)
{
	int	*binary;
	int	i;

	i = 0;
	binary = ft_itobin(getpid());
	while (i < 32)
	{
		if (binary[i] == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		i++;
	}
	free(binary);
}

void	client_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf(BHGRN" ✔ Server received message!\n"COLOR_RESET);
	}
	else
		ft_printf(BHRED"Something bad happened\n"COLOR_RESET);
	exit(0);
}

int	main(int argc, char *argv[])
{
	int					i;
	int					pid;
	struct sigaction	act;

	if (argc != 3)
	{
		ft_printf(BRED " ✖ Invalid arguments\n" COLOR_RESET);
		ft_printf(BYEL " 💡 Try &>%s <PID> <\"message\">\n", argv[0], COLOR_RESET);
		return (1);
	}
	init_act(&act, &client_handler);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGUSR1, &act, NULL);
	pid = ft_atoi(argv[1]);
	send_pid(pid);
	i = 0;
	while (argv[2][i])
	{
		send_msg(pid, argv[2][i]);
		i++;
	}
	send_msg(pid, -1);
	while (1)
		pause();
}
