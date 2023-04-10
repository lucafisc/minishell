/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/10 15:58:53 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(pwd, 1);
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
		ft_putendl_fd(*env, 1);
		env++;
	}
}

// int	main(void)
// {
// 	printf("%s\n", getenv("PWD"));
// 	ft_pwd();
// }
