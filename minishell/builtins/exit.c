/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:31:44 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/02 17:53:16 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	validate_exit_arg(char *arg)
{
	uint64_t	n;

	if (!ft_isdigit(*arg))
	{
		if (!(*arg == '+' || *arg == '-'))
			return (false);
		if (!ft_strcmp(arg, "-9223372036854775808"))
			return (true);
		arg++;
	}
	n = ft_atollu(arg);
	if (n > MAX_INT64)
		return (false);
	while (ft_isdigit(*arg))
		arg++;
	if (*arg)
		return (false);
	return (true);
}

/* Need to validate numeric argument
bash: exit: ++++1203020103: numeric argument required -> code 255 */
void	ft_exit(t_shell *s, t_command *c)
{
	uint8_t	exit_code;
	int		len;

	len = ft_arrlen(c->cmd);
	exit_code = 0;
	if (c->cmd[1])
	{
		ft_putstr_fd("exit\n", 1);
		if (!validate_exit_arg(c->cmd[1]))
		{
			ft_error("minishell", "numeric argument required", c->cmd[0], 2);
			s->exit = true;
			free_shell(s);
			exit(2);
		}
		exit_code = (uint8_t)ft_atollu(c->cmd[1]);
	}
	if (len > 2)
		return (ft_error("minishell", "too many arguments", c->cmd[0], 1));
	s->exit = true;
	free_shell(s);
	exit(exit_code);
}
