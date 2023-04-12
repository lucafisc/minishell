/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/12 14:55:13 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

/* Updates the status for the character the given matrix
is pointing to, moves on the pointer and returns a code */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	ft_update_state(char *str, int *i, int *state)
{
	int	res;

	if (!str || !state)
		return (-1);
	res = 1;
	if (*state == IN_D_QUOTE && str[*i] == '"' && str[*i - 1] != '\\')
		*state = IN_NORMAL;
	else if (*state == IN_S_QUOTE && str[*i] == '\'' && str[*i - 1] != '\\')
		*state = IN_NORMAL;
	else if (*state == IN_NORMAL && (str[*i] == '"' || str[*i] == '\'') && (*i == 0 || str[*i - 1] != '\\'))
	{
		res = 2;
		if (str[*i] == '"')
			*state = IN_D_QUOTE;
		else if (str[*i] == '\'')
			*state = IN_S_QUOTE;
	}
	else
		res = 0;
	*i += 1;
	return (res);
}

/* Checks if the given character entails a state change */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	ft_check_state(char *str, int i, int state)
{
	int	res;

	if (!str || !str[i])
		return (0);
	if ((state == IN_D_QUOTE && str[i] == '"' && str[i - 1] != '\\') || \
	(state == IN_S_QUOTE && str[i] == '\'' && str[i - 1] != '\\'))
		res = 1;
	else if (state == IN_NORMAL && (str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
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
	int	i;

	if (!str)
		return (0);
	count = 0;
	state = IN_NORMAL;
	new_cmd_flag = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_is_cmd(str[i], state))
			new_cmd_flag = ft_update_state(str, &i, &state);
		else
		{
			count++;
			while (str[i] && ft_is_cmd(str[i], state))
			{
				new_cmd_flag = ft_update_state(str, &i, &state);
				if (new_cmd_flag == 1 || ft_check_state(str, i, state) == 2)
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
	int		i;
	int		j;

	cmd = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_is_cmd(str[i], *state))
			new_cmd_flag = ft_update_state(str, &i, state);
		else
		{
			j = i;
			while (str[j] && ft_is_cmd(str[j], *state))
			{
				new_cmd_flag = ft_update_state(str, &j, state);
				if (new_cmd_flag == 1 || ft_check_state(str, j, *state) == 2)
					break ;
			}
			arr[cmd++] = ft_substr(str + i, 0, j - i);
			i = j;
		}
	}
	arr[cmd] = NULL;
	return (cmd);
}

/* It inserts s2 in s1 at the index idx substitung len chars of s1 */
/* It doesn't free the arguments */
char	*ft_strins(char *s1, char *s2, int len, int idx)
{
	int		len_s1;
	char	*ret;
	int		i;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	ret = malloc(sizeof(*ret) * (len_s1 + ft_strlen(s2) - len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < idx)
		ret[i] = s1[i];
	while (s2 && s2[i - idx])
	{
		ret[i] = s2[i - idx];
		i++;
	}
	while (s1[idx + len])
	{
		ret[i] = s1[idx + len];
		i++;
		len++;
	}
	ret[i] = '\0';
	return (ret);
}

/* It truncates s1 at the first occurrence of a char in set */
/* What's returned is freeable */
char	*ft_strtrunc(char *s1, char *set)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		return (NULL);
	ret = ft_strdup(s1);
	i = 0;
	while (set && s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				ret[i] = '\0';
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	*ft_expand_var(char *cur, char *cmds, int i)
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
char	*ft_expander(char *cmds)
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
			cmds = ft_expand_var(cur, cmds, i);
			cur = cmds;
		}
		i++;
	}
	return (cmds);
}

char	**lex_split_tokens(char *str)
{
	char	**arr;
	int		n_cmds;
	int		state;
	int		i;

	printf("\nraw string:\n%s\n", str);
	n_cmds = ft_count_cmds(str);
	printf("\nn_cmds: %d\n", n_cmds);
	arr = malloc(sizeof(*arr) * (n_cmds + 1));
	if (!arr)
		return (NULL);
	state = IN_NORMAL;
	if (ft_cmd_split(arr, str, &state) != n_cmds)
	{
		ft_free_str_arr(arr);
		arr = NULL;
	}
	i = -1;
	while (arr[++i])
		arr[i] = ft_expander(arr[i]);
	return (arr);
}
