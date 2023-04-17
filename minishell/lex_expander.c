/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:59:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/17 11:28:53 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

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
		new_cmd = ft_strins(cmds, ft_getenv(trimmed), len_trim + 1, i);
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
