/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:24:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/21 19:26:25 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int ac __attribute__((unused)), char *av[] __attribute__((unused)))
{
	int	int_mode = 1;
	while (int_mode)
	{
		int_mode = isatty(0);
		if (int_mode == 1)
		{
			write(1, "~$", 13);
		}
		/* The code continues below */
	}
}