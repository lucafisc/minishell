/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/24 17:12:09 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if the given char is part of a command
Quotes included */
t_bool	is_token(char c, int state)
{
	if (state == IN_D_QUOTE || \
	state == IN_S_QUOTE || \
	(state == IN_NORMAL && !ft_is_space(c)))
		return (true);
	return (false);
}

/* NOTE that the increment in the loops is in the */
/* ft_lex_update_status function */
/* Meaning of the new_cmd_flag values: */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	count_tokens(char *str)
{
	int	count;
	int	state;
	int	new_cmd_flag;
	int	i;

	if (!str)
		return (0);
	count = 0;
	state = IN_NORMAL;
	new_cmd_flag = 0;
	i = 0;
	while (str[i])
	{
		if (!is_token(str[i], state))
			new_cmd_flag = lex_update_state(str, &i, &state);
		else
		{
			count++;
			while (str[i] && is_token(str[i], state))
			{
				new_cmd_flag = lex_update_state(str, &i, &state);
				if (new_cmd_flag == 1 || lex_check_state(str, i, state) == 2)
					break ;
			}
		}
	}
	return (count);
}

int	split_token(char **arr, char *str, int *state)
{
	int		cmd;
	int		new_cmd_flag;
	int		i;
	int		j;
	int		space;

	cmd = 0;
	i = 0;
	while (str[i])
	{
		if (!is_token(str[i], *state))
			new_cmd_flag = lex_update_state(str, &i, state);
		else
		{
			space = 0;
			j = i;
			while (str[j] && is_token(str[j], *state))
			{
				new_cmd_flag = lex_update_state(str, &j, state);
				if (new_cmd_flag == 1 || lex_check_state(str, j, *state) == 2)
					break ;
			}
			if (str[j] == ' ')
				space = 1;
			arr[cmd++] = ft_substr(str + i, 0, j - i + space);
			i = j;
		}
	}
	arr[cmd] = NULL;
	return (cmd);
}

char	**lex_split_token(char *str)
{
	char	**arr;
	int		n_cmds;
	int		state;
	int		i;

	n_cmds = count_tokens(str);
	arr = malloc(sizeof(*arr) * (n_cmds + 1));
	if (!arr)
		return (NULL);
	state = IN_NORMAL;
	if (split_token(arr, str, &state) != n_cmds)
	{
		ft_free_str_arr(arr);
		arr = NULL;
	}
	i = -1;
	while (arr[++i])
		arr[i] = lex_expander(arr[i]);
	return (arr);
}
