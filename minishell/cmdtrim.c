/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:51:42 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/31 17:13:34 by lde-ross         ###   ########.fr       */
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
		if ((*i == 0 && !ft_is_space(cmds[*i])) || (ft_is_space(cmds[*i - 1]) && !ft_is_space(cmds[*i]))
			|| (cmds[*i - 1] == '\"' && !ft_is_space(cmds[*i])) || (cmds[*i - 1] == '\'' && !ft_is_space(cmds[*i])))
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

// t_bool	is_new_cmd_normal(char *cmds, int i, int *state)
// {
// 	if ((i == 0 && !ft_is_space(cmds[i])) || (!ft_is_space(cmds[i]) && ft_is_space(cmds[i - 1]))
// 		|| (cmds[i - 1] == '\"' && !ft_is_space(cmds[i])) || (cmds[i - 1] == '\'' && !ft_is_space(cmds[i])))
// 			return (true);
// 	if (cmds[i] == "\"")
// 		{
// 			*state = IN_D_QUOTE;
// 			return (true);
// 		}
// 	else if (cmds[i] == "\'")
// 		{
// 			*state = IN_S_QUOTE;
// 			return (true);	
// 		}
// 	return (false);
// }

t_bool	is_new_cmd(char *cmds, int i)
{
	static int	state = IN_NORMAL;

	if (state == IN_NORMAL)
		return (is_new_cmd_normal(cmds, i, &state));	
}

void	modify_state(int *state, char c)
{
	if (*state == IN_NORMAL)
		
	else if (*state == IN_D_QUOTE)
	else if (*state == IN_S_QUOTE)
}

char **cmd_trim(char *cmds)
{
	char	**arr;
	int		n_cmds;
	int		i;
	int		j;
	int		len;
	int		state;

	if (!cmds)
		return (NULL);
	n_cmds = count_cmds(cmds);
	printf("n of words: %d\n", n_cmds);
	arr = malloc(sizeof(char*) * (n_cmds + 1));
	if (!arr)
		return (NULL);
	arr[n_cmds] = NULL;
	state = IN_NORMAL;
	while (cmds[i])
	{
		modify_state(&state, cmds[i]);
		if (state == IN_NORMAL)
			
		i++;
	}
	return (arr);	
}

int main(void)
{
	char cmd[] = "\"hello      there\"\"how\"are\'you \'doing? $USER |wc -l >outfile";
	// char cmd[] = "\"hiiiii\"	hey   hi	\"hello\" abc  goodbye      ";
	cmd_trim(cmd);
	// printf("%s\n", cmd);
}
