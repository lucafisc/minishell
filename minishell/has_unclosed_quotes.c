/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:06:43 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/26 17:11:25 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_unclosed_quotes(char *str)
{
	int		i;
	t_bool	open_quotes;
	char	c;

	open_quotes = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			open_quotes = true;
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				i++;
				if (str[i] && str[i] == c)
					open_quotes = false;
			}
		}
		i++;
	}
	return (open_quotes);
}