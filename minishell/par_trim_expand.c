/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_trim_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:41:40 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 16:59:46 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_bool	is_escapable(char c)
{
	if (!c)
		return (false);
	if (c == '\"' || c == '\'' || c == '|'
		|| c == '<' || c == '>' || c == '\\')
		return (true);
	return (false);
}

int	get_len_trim_expand(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (is_escapable(str[i]) && ft_is_escaped(i, str))
			len--;
		len++;
		i++;
	}
	return (len);
}

char	*expand_escaped(char *str)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	len = get_len_trim_expand(str);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && is_escapable(str[i + 1]))
			i++;
		if (!str[i])
			break ;
		new[j] = str[i];
		i++;
		j++;
	}
	return (new);
}

t_bool	is_in_quote(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0])
		return (true);
	return (false);
}

/* Given a string without spaces it cleans it from outer quotes
keeping inner quotes. It frees the given data.
TODO Flag if a quote is not closed in the data */
char	*trim_quotes(char *data)
{
	int		i;
	int		j;
	char	*trimmed;
	char	c;

	trimmed = ft_calloc(ft_strlen(data) + 1, sizeof(*trimmed));
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (data[i])
	{
		if (ft_strchr(QUOTES, data[i]))
		{
			c = data[i];
			i++;
			while (data[i] && data[i] != c)
				trimmed[j++] = data[i++];
			i++;
		}
		else
			trimmed[j++] = data[i++];
	}
	return (trimmed);
}
