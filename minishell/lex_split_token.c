/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/26 15:07:23 by lde-ross         ###   ########.fr       */
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
// int	count_tokens(char *str)
// {
// 	int	count;
// 	int	state;
// 	int	new_cmd_flag;
// 	int	i;

// 	if (!str)
// 		return (0);
// 	count = 0;
// 	state = IN_NORMAL;
// 	new_cmd_flag = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!is_token(str[i], state))
// 			new_cmd_flag = lex_update_state(str, &i, &state);
// 		else
// 		{
// 			count++;
// 			while (str[i] && is_token(str[i], state))
// 			{
// 				new_cmd_flag = lex_update_state(str, &i, &state);
// 				if (new_cmd_flag == 1 || lex_check_state(str, i, state) == 2)
// 					break ;
// 			}
// 		}
// 	}
// 	return (count);
// }

int	split_token(char **arr, char *str, int *state)
{
	int		cmd;
	int		new_cmd_flag;
	int		i;
	int		j;

	cmd = 0;
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
			arr[cmd++] = ft_substr(str + i, 0, j - i);
			i = j;
		}
	}
	arr[cmd] = NULL;
	return (cmd);
}

t_bool	is_next_new_tok(char *str, int i)
{
	if ((ft_is_space(str[i]) && !ft_is_space(str[i + 1]) && str[i + 1]) || (i == 0 && !ft_is_space(str[i])))
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
		//printf("checking str[%d]:%c\n", i, str[i]);
		if (is_next_new_tok(str, i))
		{
			count++;
			//printf("count is now %d\n", count);
		}
		if (str[i] == '\"' || str[i] == '\'')
			i = ft_skip_char(str, str[i], i);
		i++;
	}
	return (count);
}

void	ft_update_state(char c, int *state, int *prev_state)
{
	if (!ft_strchr(QUOTES, c))
		return ;
	// open quotes
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
    // close quotes
	else if ((*state == IN_S_QUOTE && c == S_QUOTE) || \
	(*state == IN_D_QUOTE && c == D_QUOTE))
	{
		*state = *prev_state;
		*prev_state = IN_NORMAL;
	}
}

int	is_new_wo(char const *s, int i, int state, int prev_state)
{
	int	initial_state;

	initial_state = state;
	if ((!ft_is_space(s[i]) && ft_is_space(s[i - 1])) || (i == 0 && !ft_is_space(s[i])))
	{
		if (!ft_strchr(QUOTES, s[i]) && state == IN_NORMAL)
			return (1);
		if (ft_strchr(QUOTES, s[i]))
		{
			ft_update_state(s[i], &state, &prev_state);
			if (state != initial_state && initial_state == IN_NORMAL)
				return (1);
		}
	}
	return (0);
}

int	ft_count_tokens_by_char(char *str)
{
	int	state;
	int	prev_state;
	int	i;
	int	count;

	count = 0;
	state = IN_NORMAL;
	prev_state = state;
	i = 0;
	while (str[i])
	{
		if (is_new_wo(str, i, state, prev_state))
			count++;
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			ft_update_state(str[i], &state, &prev_state);
		i++;
	}
	return (count);
}

char	**lex_split_token(char *str)
{
	int		n_cmds;
	char	**arr;
	int		i;
	int		start;
	int		len = 0;
	int		prev;
	int		j;

	n_cmds = count_tokens(str);

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
	//printf("\n\n\n_________\n");
	i = -1;
	while (arr[++i])
		arr[i] = lex_expander(arr[i]);
	//ft_print_strarr(arr);
	return(arr);
}
