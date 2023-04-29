/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:54:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/29 15:18:20 by tfregni          ###   ########.fr       */
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

char	*fill_new_token(char *str, int *i)
{
	char	*arr;
	int		start;
	int		len;
	int		prev;

	if (*i != 0)
		*i += 1;
	start = *i;
	len = 0;
	while (str[*i] && !ft_is_space(str[*i]))
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			prev = *i;
			*i = ft_skip_char(str, str[*i], *i);
			len += *i + 1 - prev;
		}
		else
			len++;
		*i += 1;
	}
	arr = ft_substr(str, start, len);
	return (arr);
}

/* Splits the str to an array. The return is freeable */
char	**lex_split_token(char *str)
{
	int		n_cmds;
	char	**arr;
	int		i;
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
			arr[j] = fill_new_token(str, &i);
			j++;
		}
		else
			i++;
	}
	return (arr);
}
