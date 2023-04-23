/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:59:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/22 00:18:56 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*retrieve_param(char *key)
{
	int		len;
	int		i;
	char	**params;

	params = g_shell->params;
	if (!params)
		return (NULL);
	len = ft_strlen(key);
	i = ft_arrlen(params);
	while (--i >= 0 && params[i])
	{
		if (!ft_strncmp(params[i], key, len) && params[i][len] == '=')
			return (params[i] + len + 1);
	}
	return (ft_getenv(key));
}

char	*expand_var(char *cur, char *cmds, int i)
{
	char	*trimmed;
	int		len_trim;
	char	*new_cmd;

	if (cur[i] == '~')
		new_cmd = ft_strins(cmds, ft_getenv("HOME"), 1, i);
	else
	{
		trimmed = ft_strtrunc(&cur[i + 1], TRAIL_CHAR);
		len_trim = ft_strlen(trimmed);
		new_cmd = ft_strins(cmds, retrieve_param(trimmed), len_trim + 1, i);
		free(trimmed);
	}
	free(cmds);
	return (new_cmd);
}

char	*lex_expander(char *cmds)
{
	char	*cur;
	int		i;

	if (!cmds || *cmds == '\'')
		return (cmds);
	cur = cmds;
	i = 0;
	while (cur[i])
	{
		if (cur[i] == '~' || cur[i] == '$')
		{
			cmds = expand_var(cur, cmds, i);
			cur = cmds;
		}
		i++;
	}
	return (cmds);
}
