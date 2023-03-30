/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdw_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/30 12:38:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

void	ft_env(char **env)
{
	if (!env)
		return ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
