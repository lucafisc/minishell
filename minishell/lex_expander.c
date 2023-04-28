/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:59:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/28 21:05:13 by tfregni          ###   ########.fr       */
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

void	add_flag_char(char **data)
{
	char	*flagged;
	int		len;
	int		i;

	len = ft_strlen(*data);
	flagged = ft_calloc(sizeof(*flagged), len + 2);
	if (!flagged)
		return ;
	ft_strlcpy(flagged, *data, len + 1);
	i = 0;
	while (flagged[i])
		i++;
	flagged[i] = (char) FLAG_CHAR;
	// free(*data);
	*data = flagged;
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
	printf("expand_var before flag\n");
	add_flag_char(&new_cmd);
	// printf("Flagged: %s\n", new_cmd);
	free(cmds);
	return (new_cmd);
}

void	ft_update_state(char c, int *state, int *prev_state)
{
	if (!ft_strchr(QUOTES, c))
		return ;
	if (*state == IN_NORMAL || \
	(*state == IN_S_QUOTE && c == D_QUOTE) || \
	(*state == IN_D_QUOTE && c == S_QUOTE))
	{
		*prev_state = *state;
		if (c == S_QUOTE)
			*state = IN_S_QUOTE;
		else
			*state = IN_D_QUOTE;
	}
	else if ((*state == IN_S_QUOTE && c == S_QUOTE) || \
	(*state == IN_D_QUOTE && c == D_QUOTE))
	{
		*state = *prev_state;
		*prev_state = IN_NORMAL;
	}
}

char	*lex_expander(char *cmds)
{
	char	*cur;
	int		i;
	int		state;
	int		prev_state;

	if (!cmds)
		return (cmds);
	cur = cmds;
	i = 0;
	state = IN_NORMAL;
	prev_state = state;
	while (cur[i])
	{
		ft_update_state(cur[i], &state, &prev_state);
		if ((cur[i] == '~' && state != IN_S_QUOTE) || \
		(cur[i] == '$' && !(state == IN_S_QUOTE && prev_state == IN_NORMAL)))
		{
			cmds = expand_var(cur, cmds, i);
			cur = cmds;
		}
		i++;
	}
	return (cmds);
}

char	**expander(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		arr[i] = lex_expander(arr[i]);
		i++;
	}
	return (arr);
}
