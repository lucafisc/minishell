/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_trim_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:41:40 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/30 14:29:38 by tfregni          ###   ########.fr       */
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

static void	copy_quote_content(char **dst, char *src)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (ft_strchr(QUOTES, src[i]))
		{
			c = src[i];
			i++;
			while (src[i] && src[i] != c)
				(*dst)[j++] = src[i++];
			i++;
		}
		else
			(*dst)[j++] = src[i++];
	}
}

/* Given a string without spaces it cleans it from outer quotes
keeping inner quotes */
char	*trim_quotes(char *data)
{
	char	*trimmed;

	if (!ft_strchr(data, FLAG_CHAR))
	{
		trimmed = ft_calloc(ft_strlen(data) + 1, sizeof(*trimmed));
		if (!trimmed)
			return (NULL);
		copy_quote_content(&trimmed, data);
		return (trimmed);
	}
	*ft_strchr(data, FLAG_CHAR) = '\0';
	return (ft_strdup(data));
}
