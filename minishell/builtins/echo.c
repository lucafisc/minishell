/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:46:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/02 17:54:33 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag_in_token(char *str)
{
	int	j;

	j = 1;
	if (str && ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[j] == 'n')
			j++;
		if (!str[j])
			return (true);
	}
	return (false);
}

t_bool	check_echo_flag(char **args, int *i)
{
	t_bool		flag;

	flag = 0;
	if (is_flag_in_token(args[*i]))
	{
		flag = true;
		(*i)++;
		while (is_flag_in_token(args[(*i)]))
			(*i)++;
	}
	return (flag);
}

void	ft_echo(t_shell *s, t_command *c)
{
	char	**args;
	t_bool	n;
	int		i;

	(void) s;
	if (!c || !c->cmd)
		return ;
	args = c->cmd;
	i = 1;
	n = check_echo_flag(args, &i);
	while (args[i])
	{
		ft_putstr_fd(args[i], c->outfile);
		if (args[i][0] && args[i + 1])
			ft_putchar_fd(' ', c->outfile);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', c->outfile);
}
