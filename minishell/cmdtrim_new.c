/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/02 20:37:57 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

/* Updates the status for the character the given matrix
is pointing to, moves on the pointer and returns a code */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	ft_update_state(char **str, int *state)
{
	int	res;

	if (!str || !state)
		return (-1);
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

char	*ft_insstr(char *s1, char *s2, int len, int idx)
{
	int		len_s1;
	char	*ret;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	ret = malloc(sizeof(*ret) * (len_s1 + ft_strlen(s2) - len + 1));
	i = -1;
	while (++i < idx)
		ret[i] = s1[i];
	while (s2[i - idx])
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
	//free(s1);
	//free(s2);
	return (ret);
}

//"HELLO $USER WORLD"
//

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
			// printf("%c vs %c\n", s1[i], set[j]);
			if (s1[i] == set[j])
			{
				// printf("terminating at %c\n", s1[i]);
				ret[i] = '\0';
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (s1);
}


char	*ft_expand_var(char **cur, char *cmds, int steps)
{
	char	*trimmed;
	int		len_trim;
	int		len_expanded;
	char	*new_cmd;

	trimmed = ft_strtrunc(*cur, TRAIL_CHAR);
	len_trim = ft_strlen(trimmed);
	len_expanded = ft_strlen(getenv(trimmed));
	write(1, "here\n", 5);
	new_cmd = ft_strnjoin(3, cmds, getenv(trimmed), (*cur + len_trim));
	*cur = new_cmd + steps + len_expanded;
	printf("getenv:%s\n", getenv("bullshit"));
	free(cmds);
	free(trimmed);
	return (new_cmd);
}

/* At the moment the lookup is in the "real" environment */
char	*ft_expander(char *cmds)
{
	int		state;
	char	*cur;
	int		steps;

	if (!cmds || *cmds == '\'')
		return (cmds);
	state = IN_NORMAL;
	cur = cmds;
	steps = 0;
	while (*cur)
	{
		ft_update_state(&cur, &state);
		steps++;
		if (*(cur - 1) == '~')
		{
			steps -= 1;
			cmds = ft_insstr(cmds, "$HOME", 1, steps);
			printf("cmds: %s\n", cmds);
			cur = &cmds[steps + 1];
			printf("new cur: %s\n", cur);
		}
		else if (*(cur - 1) == '$')
		{
			char *expanded = getenv(ft_strtrunc(cur, TRAIL_CHAR));
			write(1, "bla", 3);
			// *(cur - 1) = '\0';
			// cmds = ft_expand_var(&cur, cmds, steps);
			cmds = ft_insstr(cmds, expanded, 5, steps - 1);
		}
	}
	return (NULL);
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
	while (*arr)
	{
		printf("%s\n", ft_expander(*arr));
		arr++;
	}
	return (arr);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	g_env = env;
	// // char cmd[] = "    \"hello      there\"\"how\"are\'you \'doing? $USER |wc -l >outfile";
	// // char cmd[] = "\"hiiiii\"	hey   hi	\"hello\" abc  goodbye      ";
	// char cmd[] = "\"these are 'single quotes' in double quotes\" and \"hi$USER | $PATH in d_quotes\" 'and$HOME in s_quotes'| '\"double quotes\" in single'\"followed by\" a command without'space'";
	char cmd[] = "\"hi$USER| ~in d_quotes\"";
	char **cmds = ft_cmd_trim(cmd);
	ft_print_strarr(cmds);
	// printf("%s\n", cmd);
	ft_free_str_arr(cmds);
	// // printf("%s\n", ft_strtrunc("$USER| bla ><|", "| <>"));
	// printf("%s", ft_insstr("Insert", "Middle", 2, 3));
}

/*
    "hello      there""how"are'you 'doing? $USER |wc -l >outfile
    1                 2    3  4     5      6     7   8  9
	"hiiiii"	hey   hi	"hello" abc  goodbye
	1           2     3     4       5    6
*/
