/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_trim_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:41:40 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/29 12:23:32 by tfregni          ###   ########.fr       */
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

void	add_flag_char(char **data)
{
	char	*flagged;
	int		len;
	int		i;

	len = ft_strlen(*data);
	flagged = ft_calloc(sizeof(*flagged), len + 2);
	if (!flagged)
		return ;
	ft_strlcpy(flagged, *data, len + 1);
	i = 0;
	while (flagged[i])
		i++;
	flagged[i] = (char) FLAG_CHAR;
	*data = flagged;
}

/* Given a string without spaces it cleans it from outer quotes
keeping inner quotes */
char	*trim_quotes(char *data)
{
	int		i;
	int		j;
	char	*trimmed;
	char	c;

	i = 0;
	j = 0;
	// printf("trim quotes to %s\n", data);
	if (!ft_strchr(data, FLAG_CHAR))
	{
		trimmed = ft_calloc(ft_strlen(data) + 1, sizeof(*trimmed));
		if (!trimmed)
			return (data);
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
		// printf("trim_quotes trimmed %p\n", trimmed);
		return (trimmed);
	}
	*ft_strchr(data, FLAG_CHAR) = '\0';
	return (data);
}
