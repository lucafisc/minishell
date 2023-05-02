/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:22:43 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/02 10:03:09 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_status(int status)
{
	char	*stat;
	char	*value;
	uint8_t	err_code;

	if (status > 255)
		status = status / 255;
	err_code = (uint8_t)status;
	stat = ft_itoa(err_code);
	value = ft_strjoin("?=", stat);
	free(stat);
	g_shell->params = env_append(g_shell->params, value);
	free(value);
}

int	throw_err(char *str, char *arg)
{
	if (str && str[0])
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	if (arg && arg[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	write(2, "\n", 1);
	return (1);
}

/* It takes up to 3 strings to describe the error, if error_code is
positive it adds it to $? */
void	ft_error(char *general, char *err, char *arg, uint8_t error_code)
{
	if (general && general[0])
	{
		ft_putstr_fd(general, 2);
	}
	if (err && err[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err, 2);
	}
	if (arg && arg[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putendl_fd("", 2);
	if (error_code >= 0)
	{
		g_shell->status = error_code;
		add_status(g_shell->status);
	}
}
