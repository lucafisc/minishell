/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:34:19 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 13:35:05 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	inherit_env(t_pipe *p, char **envp)
{
	int	i;

	i = 0;
	p->env = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	if (!p->env)
		ft_exit("pipex: Out of memory: inherit_env\n", 1);
	while (envp[i])
	{
		p->env[i] = ft_strdup(envp[i]);
		if (!p->env[i])
		{
			ft_free_str_arr(p->env);
			ft_exit("pipex: Out of memory: inherit_env\n", 1);
		}
		i++;
	}
	p->env[i] = 0;
}
