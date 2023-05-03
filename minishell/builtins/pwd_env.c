/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/03 18:42:52 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_shell *s, t_command *c)
{
	char	pwd[PATH_MAX];

	(void) s;
	(void) c;
	getcwd(pwd, sizeof(pwd));
	ft_putendl_fd(pwd, 1);
}

void	ft_env(t_shell *s, t_command *c)
{
	char	**env;

	(void) c;
	env = s->env;
	if (!env)
		return ;
	while (*env)
	{
		ft_putendl_fd(*env, c->outfile);
		env++;
	}
}
