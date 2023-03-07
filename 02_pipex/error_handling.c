/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:42 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 21:15:30 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *name, char *desc)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(desc, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_exit(const char *msg, int code)
{
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	else
		perror("pipex");
	exit(code);
}
