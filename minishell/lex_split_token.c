/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/27 18:11:36 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if the given char is part of a command
Quotes included */
t_bool	is_token(char c, int state)
{
	if (state == IN_D_QUOTE
		||state == IN_S_QUOTE
		|| (state == IN_NORMAL && !ft_is_space(c)))
		return (true);
	return (false);
}

void	loop_token(int *state, int *cmd, char **arr, char *str)
{
	int	j;
	int	new_cmd_flag;
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_token(str[i], *state))
			new_cmd_flag = lex_update_state(str, &i, state);
		else
		{
			j = i;
			while (str[j] && is_token(str[j], *state))
			{
				new_cmd_flag = lex_update_state(str, &j, state);
				if (new_cmd_flag == 1 || lex_check_state(str, j, *state) == 2)
					break ;
			}
			arr[*cmd++] = ft_substr(str + i, 0, j - i);
			i = j;
		}
	}
}

int	split_token(char **arr, char *str, int *state)
{
	int	cmd;

	cmd = 0;
	loop_token(state, &cmd, arr, str);
	arr[cmd] = NULL;
	return (cmd);
}

t_bool	is_next_new_tok(char *str, int i)
{
	if ((ft_is_space(str[i]) && !ft_is_space(str[i + 1]) && str[i + 1])
		|| (i == 0 && !ft_is_space(str[i])))
		return (true);
	return (false);
}

int	count_tokens(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_next_new_tok(str, i))
			count++;
		if (str[i] == '\"' || str[i] == '\'')
			i = ft_skip_char(str, str[i], i);
		i++;
	}
	return (count);
}

char	**lex_split_token(char *str)
{
	int		n_cmds;
	char	**arr;
	int		i;
	int		j;
	int		start;
	int		len;
	int		prev;

	n_cmds = count_tokens(str);
	len = 0;
	arr = malloc(sizeof(*arr) * (n_cmds + 1));
	if (!arr)
		return (NULL);
	arr[n_cmds] = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_next_new_tok(str, i))
		{
			if (i != 0)
				i++;
			start = i;
			len = 0;
			while (str[i] && !ft_is_space(str[i]))
			{
				if (str[i] == '\"' || str[i] == '\'')
				{
					prev = i;
					i = ft_skip_char(str, str[i], i);
					i++;
					len += i - prev;
				}
				else
				{
					i++;
					len++;
				}
			}
			arr[j] = ft_substr(str, start, len);
			j++;
		}
		else
			i++;
	}
	i = -1;

	return (arr);
}
