/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:59:28 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/03 17:04:02 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(char *cur, char *cmds, int i)
{
	char	*trimmed;
	int		len_trim;
	char	*new_cmd;
	char	*param;

	if (cur[i] == '~')
		new_cmd = ft_strins(cmds, ft_getenv("HOME"), 1, i);
	else
	{
		trimmed = trim_param(cur, i);
		len_trim = ft_strlen(trimmed);
		if (len_trim == 0)
			new_cmd = ft_strins(cmds, "$", len_trim + 1, i);
		else
		{
			param = retrieve_param(trimmed);
			new_cmd = ft_strins(cmds, param, len_trim + 1, i);
			if (param && (ft_strchr(param, QUOTES[0]) || \
			ft_strchr(param, QUOTES[1])))
				add_flag_char(&new_cmd);
		}
		free(trimmed);
	}
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
	while (cur && cur[i])
	{
		ft_update_state(cur[i], &state, &prev_state);
		if ((cur[i] == '~' && state != IN_S_QUOTE) || \
		(cur[i] == '$' && !(state == IN_S_QUOTE && prev_state == IN_NORMAL)))
		{
			cmds = expand_var(cur, cmds, i);
			if (cmds[i] == '$')
				i++;
			free(cur);
			cur = cmds;
		}
		else
			i++;
	}
	return (cmds);
}

char	**expander(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		arr[i] = lex_expander(arr[i]);
		i++;
	}
	return (arr);
}
