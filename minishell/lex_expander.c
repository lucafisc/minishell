/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:59:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 18:42:36 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*retrieve_param(char *key)
{
	int		len;
	int		i;
	char	**params;

	params = g_shell->params;
	printf("retrieve\n");
	ft_print_strarr(params);
	if (params)
	{
		len = ft_strlen(key);
		i = ft_arrlen(params);
		while (--i >= 0 && params[i])
		{
			if (!ft_strncmp(params[i], key, len) && params[i][len] == '=')
			{
				printf("retrieve par: %s\n", params[i]);
				return (params[i] + len + 1);
			}
		}
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
		if (len_trim == 0)
			new_cmd = ft_strins(cmds, "$", len_trim + 1, i);
		else
			new_cmd = ft_strins(cmds, retrieve_param(trimmed), len_trim + 1, i);
		free(trimmed);
	}
	free(cmds);
	return (new_cmd);
}

// char	*lex_expander(char *cmds)
// {
// 	char	*cur;
// 	int		i;

// 	if (!cmds || *cmds == '\'')
// 		return (cmds);
// 	cur = cmds;
// 	i = 0;
// 	while (cur[i])
// 	{
// 		// printf("lex_expander: %c\n", cur[i]);
// 		if (cur[i] == '~' || cur[i] == '$')
// 		{
// 			cmds = expand_var(cur, cmds, i);
// 			cur = cmds;
// 		}
// 		i++;
// 	}
// 	return (cmds);
// }

char	*lex_expander(char *cmds)
{
	char	*cur;
	int		i;
	int		state;
	int		prev_state;

	if (!cmds)
		return (cmds);
	printf("expander cmd: %s\n", cmds);
	cur = cmds;
	i = 0;
	state = IN_NORMAL;
	prev_state = state;
	while (cur[i])
	{
		// printf("before %c -> state: %d\n", cur[i], state);
		ft_update_state(cur[i], &state, &prev_state);
		// printf("after  %c -> state: %d\n", cur[i], state);
		if ((cur[i] == '~' && state != IN_S_QUOTE) || \
		(cur[i] == '$' && !(state == IN_S_QUOTE && prev_state == IN_NORMAL)))
		// if ((cur[i] == '~' || cur[i] == '$') && state != IN_S_QUOTE)
		{
			cmds = expand_var(cur, cmds, i);
			printf("expander cmd expanded: %s\n", cmds);
			cur = cmds;
		}
		i++;
	}
	return (cmds);
}
