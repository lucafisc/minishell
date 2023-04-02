/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/02 08:18:04 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Updates the status for the given character and returns a code */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	ft_update_state(char **str, int *state)
{
	int	res;

	res = 1;
	if (*state == IN_D_QUOTE && **str == '"')
		*state = IN_NORMAL;
	else if (*state == IN_S_QUOTE && **str == '\'')
		*state = IN_NORMAL;
	else if (*state == IN_NORMAL && (**str == '"' || **str == '\''))
	{
		res = 2;
		if (**str == '"')
			*state = IN_D_QUOTE;
		else if (**str == '\'')
			*state = IN_S_QUOTE;
	}
	else
		res = 0;
	(*str)++;
	return (res);
}

/* Checks if the given character entails a state change */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	ft_check_state(char c, int state)
{
	int	res;

	if (!c)
		return (0);
	if ((state == IN_D_QUOTE && c == '"') || \
	(state == IN_S_QUOTE && c == '\''))
		res = 1;
	else if (state == IN_NORMAL && (c == '"' || c == '\''))
		res = 2;
	else
		res = 0;
	return (res);
}

/* Checks if the given char is part of a command
Quotes included */
t_bool	ft_is_cmd(char c, int state)
{
	if (state == IN_D_QUOTE || \
	state == IN_S_QUOTE || \
	(state == IN_NORMAL && !ft_is_space(c)))
		return (true);
	return (false);
}

/* NOTE that the increment in the loops is in the ft_update_status function */
/* Meaning of the new_cmd_flag values: */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	ft_count_cmds(char *str)
{
	int	count;
	int	state;
	int	new_cmd_flag;

	if (!str)
		return (0);
	count = 0;
	state = IN_NORMAL;
	new_cmd_flag = 0;
	while (*str)
	{
		if (!ft_is_cmd(*str, state))
			new_cmd_flag = ft_update_state(&str, &state);
		else
		{
			count++;
			while (*str && ft_is_cmd(*str, state))
			{
				new_cmd_flag = ft_update_state(&str, &state);
				if (new_cmd_flag == 1 || ft_check_state(*str, state) == 2)
					break ;
			}
		}
	}
	return (count);
}

int	ft_cmd_split(char **arr, char *str, int *state)
{
	int		cmd;
	int		new_cmd_flag;
	char	*cur;

	cmd = 0;
	while (*str)
	{
		if (!ft_is_cmd(*str, *state))
			new_cmd_flag = ft_update_state(&str, state);
		else
		{
			cur = str;
			while (*cur && ft_is_cmd(*cur, *state))
			{
				new_cmd_flag = ft_update_state(&cur, state);
				if (new_cmd_flag == 1 || ft_check_state(*cur, *state) == 2)
					break ;
			}
			arr[cmd++] = ft_substr(str, 0, cur - str);
			str = cur;
		}
	}
	arr[cmd] = NULL;
	return (cmd);
}

char	**ft_cmd_trim(char *str)
{
	char	**arr;
	int		n_cmds;
	int		state;

	n_cmds = ft_count_cmds(str);
	printf("n_cmds: %d\n", n_cmds);
	arr = malloc(sizeof(*arr) * (n_cmds + 1));
	if (!arr)
		return (NULL);
	state = IN_NORMAL;
	if (ft_cmd_split(arr, str, &state) != n_cmds)
	{
		ft_free_str_arr(arr);
		arr = NULL;
	}
	return (arr);
}

int	main(void)
{
	// char cmd[] = "    \"hello      there\"\"how\"are\'you \'doing? $USER |wc -l >outfile";
	// char cmd[] = "\"hiiiii\"	hey   hi	\"hello\" abc  goodbye      ";
	char cmd[] = "\"these are 'single quotes' in double quotes\" and '\"double quotes\" in single'\"followed by\" a command without'space'";

	char **cmds = ft_cmd_trim(cmd);
	ft_print_strarr(cmds);
	// printf("%s\n", cmd);
	ft_free_str_arr(cmds);
}

/*
    "hello      there""how"are'you 'doing? $USER |wc -l >outfile
     1                 2   3   4    5      6     7   8  9
	"hiiiii"	hey   hi	"hello" abc  goodbye
	1           2     3     4       5    6
*/
