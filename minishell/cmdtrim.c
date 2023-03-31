/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:51:42 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/31 21:59:59 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN_NORMAL,
// IN_S_QUOTE,
// IN_D_QUOTE,

void count_in_normal(char *cmds, int *i, int *count, int *state)
{
	while (cmds[*i])
	{
		if (cmds[*i] == '"')
			*state = IN_D_QUOTE;
		else if (cmds[*i] == '\'')
			*state = IN_S_QUOTE;
		if (*state != IN_NORMAL)
			break;
		if ((*i == 0 && !ft_is_space(cmds[*i])) || (ft_is_space(cmds[*i - 1]) && !ft_is_space(cmds[*i])) || (cmds[*i - 1] == '\"' && !ft_is_space(cmds[*i])) || (cmds[*i - 1] == '\'' && !ft_is_space(cmds[*i])))
			*count += 1;
		*i += 1;
	}
}

void count_in_d_quote(char *cmds, int *i, int *count, int *state)
{
	int first_quote_index;

	first_quote_index = *i;
	while (cmds[*i])
	{
		if (*i != first_quote_index && cmds[*i] == '\"')
		{
			*state = IN_NORMAL;
			*i += 1;
			*count += 1;
			break;
		}
		*i += 1;
	}
}

void count_in_s_quote(char *cmds, int *i, int *count, int *state)
{
	int first_quote_index;

	first_quote_index = *i;
	while (cmds[*i])
	{
		if (*i != first_quote_index && cmds[*i] == '\'')
		{
			*state = IN_NORMAL;
			*i += 1;
			*count += 1;
			break;
		}
		*i += 1;
	}
}

int count_cmds(char *cmds)
{
	int i;
	int count;
	int state;

	i = 0;
	count = 0;
	state = IN_NORMAL;
	while (cmds[i])
	{
		if (state == IN_NORMAL)
			count_in_normal(cmds, &i, &count, &state);
		else if (state == IN_D_QUOTE)
			count_in_d_quote(cmds, &i, &count, &state);
		else if (state == IN_S_QUOTE)
			count_in_s_quote(cmds, &i, &count, &state);
	}
	return (count);
}

// t_bool is_new_cmd(int *state, char *cmds, int i)
// {
// 	if (*state == IN_NORMAL)
// 	{
// 	}
// 	else if (*state == IN_D_QUOTE)
// 	{

// 	}
// 	else if (*state == IN_S_QUOTE)
// 	{
// 	}
// }

// void populate_cmds(char **arr, int n_cmds, char *cmds)
// {
// 	int i;
// 	int state;

// 	i = 0;
// 	state = IN_NORMAL;
// 	while (str[i] && n_cmds > 0)
// 	{
// 		if (is_new_cmd(&state, cmds, i))

// 			i++;
// 	}
// }

// char **cmd_trim(char *cmds)
// {
// 	char **arr;
// 	int n_cmds;
// 	int i;

// 	if (!cmds)
// 		return (NULL);
// 	n_cmds = count_cmds(cmds);
// 	printf("n of words: %d\n", n_cmds);
// 	arr = malloc(sizeof(char *) * (n_cmds + 1));
// 	if (!arr)
// 		return (NULL);
// 	arr[n_cmds] = NULL;
// 	populate_cmds(arr, n_cmds, cmds);
// 	return (arr);
// }

/*
(*i == 0 && !ft_is_space(cmds[*i])) ||
(ft_is_space(cmds[*i - 1]) && !ft_is_space(cmds[*i])) ||
(cmds[*i - 1] == '\"' && !ft_is_space(cmds[*i])) ||
(cmds[*i - 1] == '\'' && !ft_is_space(cmds[*i])) */
t_bool	ft_is_cmd(char **str, int *state)
{
	printf("%c: state %d\n", **str, *state);
	if (*state == IN_D_QUOTE)
	{
		if (**str == '\"')
			*state = IN_NORMAL;
		return (true);
	}
	else if (*state == IN_S_QUOTE)
	{
		if (**str == '\'')
			*state = IN_NORMAL;
		return (true);
	}
	else
	{
		if (ft_is_space(**str))
			return (false);
		if (**str == '\'')
			*state = IN_S_QUOTE;
		else if (**str == '\"')
			*state = IN_D_QUOTE;
		return (true);
	}
}

int	ft_count_cmds(char *str)
{
	int	count;
	int	state;
	int	cmd_state;

	if (!str)
		return (0);
	count = 0;
	state = IN_NORMAL;
	while (*str)
	{
		cmd_state = state;
		printf("updating cmd_state\n");
		if (!ft_is_cmd(&str, &state))
			str++;
		else
		{
			if (state != cmd_state)
			{
				str++;
				continue ;
			}
			count++;
			printf("new cmd starting at %c\n", *str);
			while (*str && ft_is_cmd(&str, &state) && state == cmd_state)
			{
				// printf("inner loop\n");
				str++;
			}
		}
	}
	return (count);
}

void	ft_cmd_trim(char *str)
{
	// char	**arr;
	int		n_cmds;

	n_cmds = ft_count_cmds(str);
	printf("n_cmds: %d\n", n_cmds);
}

int main(void)
{
	char cmd[] = "\"hello      there\"\"how\"are\'you \'doing? $USER |wc -l >outfile";
	// char cmd[] = "\"hiiiii\"	hey   hi	\"hello\" abc  goodbye      ";
	ft_cmd_trim(cmd);
	// printf("%s\n", cmd);
}

/*
"hello      there""how"are'you 'doing? $USER |wc -l >outfile
1                 2    3  4     5      6     7   8  9
*/
