/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:51:42 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/30 18:21:39 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// IN_NORMAL,
	// IN_S_QUOTE,
	// IN_D_QUOTE,

void	count_in_normal(char *cmds, int *i, int *count, int *state)
{
	while (cmds[*i])
	{
		if (cmds[*i] == '"')
			*state = IN_D_QUOTE;
		else if (cmds[*i] == '\'')
			*state = IN_S_QUOTE;
		if (*state != IN_NORMAL)
			break;
		if (!ft_is_space(cmds[*i]))
			*count += 1;
		*i += 1;
	}
	
}

int	count_cmds(char *cmds)
{
	int	i;
	int	count;
	int	state;

	i = 0;
	count = 0;
	state = IN_NORMAL;
	while (cmds[i])
	{
		if (state == IN_NORMAL)
			count_in_normal(cmds, &i, &count, &state);
		else if (state == IN_D_QUOTE)
			//count_in_d_quote()
		else if (state == IN_S_QUOTE)
			//count_in_s_quote()
	}
	return (count)
}

char **cmd_trim(char *cmds)
{
	int		n_cmds;
	char	**arr;
	
	if (!cmds)
		return (NULL);
	n_cmds = count_cmds(cmds);
}

int	main(void)
{
	// char cmd[] = "\"hello      there\" how are \'you \'doing? $USER |wc -l >outfile";
	char cmd[] = "hey   hi	\"hello\"   goodbye";

	printf("%s\n", cmd);
}