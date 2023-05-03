/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:25 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/03 17:04:08 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*retrieve_param(char *key)
{
	int		len;
	int		i;
	char	**params;

	params = g_shell->params;
	if (params)
	{
		len = ft_strlen(key);
		i = ft_arrlen(params);
		while (--i >= 0 && params[i])
		{
			if (!ft_strncmp(params[i], key, len) && params[i][len] == '=')
				return (params[i] + len + 1);
		}
	}
	return (ft_getenv(key));
}

char	*trim_param(char *cur, int i)
{
	if (!ft_strncmp(&cur[i + 1], "?", 1))
		return (ft_strdup("?"));
	return (ft_strtrunc(&cur[i + 1], TRAIL_CHAR));
}
