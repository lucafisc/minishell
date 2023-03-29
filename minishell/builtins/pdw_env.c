/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdw_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/29 19:15:17 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}