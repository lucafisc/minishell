/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:59:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/13 11:48:24 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(char *cur, char *cmds, int i)
{
	char	*trimmed;
	int		len_trim;
	char	*new_cmd;

	if (cur[i] == '~')
		new_cmd = ft_strins(cmds, getenv("HOME"), 1, i);
	else
	{
		trimmed = ft_strtrunc(&cur[i + 1], TRAIL_CHAR);
		len_trim = ft_strlen(trimmed);
		new_cmd = ft_strins(cmds, getenv(trimmed), len_trim + 1, i);
		free(trimmed);
	}
	free(cmds);
	return (new_cmd);
}

/* At the moment the lookup is in the "real" environment */
/* Try double=hi$USER;echo $double */
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
