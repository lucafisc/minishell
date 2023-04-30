/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:31:44 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/30 14:46:26 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	validate_exit_arg(char *arg)
{
	if (!ft_isdigit(*arg))
	{
		if (!(*arg == '+' || *arg == '-'))
			return (false);
		arg++;
	}
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

	trim_cmd(&c);
	len = ft_arrlen(c->cmd);
	exit_code = 0;
	if (c->cmd[1])
	{
		if (!validate_exit_arg(c->cmd[1]))
		{
			ft_error("minishell", "numeric argument required", c->cmd[0], 255);
			s->exit = true;
			free_shell(s);
			exit(255);
		}
		exit_code = (uint8_t)ft_atoi(c->cmd[1]);
	}
	if (len > 2)
		return (ft_error("minishell", "too many arguments", c->cmd[0], 1));
	s->exit = true;
	free_shell(s);
	exit(exit_code);
}
