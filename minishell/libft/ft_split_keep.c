/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:57:02 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 20:38:17 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words_keep(char *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			if (s[i + 1] && s[i + 1] == c && c != '|')
				i++;
		}
		else if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_skip_char(s, s[i], i);
		i++;
	}
	return (count);
}

size_t	str_siz_keep(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != c))
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_skip_char(s, s[i], i);
		i++;
	}
	return (i);
}

char	*keep_char(char *s, char c, int *i)
{
	char	*str;

	if (s[*i + 1] == c && c != '|')
	{
		str = ft_calloc(3, sizeof(char));
		str[0] = c;
		str[1] = c;
		*i += 1;
	}
	else
	{
		str = ft_calloc(2, sizeof(char));
		str[0] = c;
	}	
	return (str);
}

char	**ft_split_keep(char *s, char c)
{
	int		words;
	char	**arr;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	words = count_words_keep(s, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (0);
	arr[words] = NULL;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			arr[j] = keep_char(s, c, &i);
			i++;
		}
		else
		{
			len = str_siz_keep((s + i), c);
			arr[j] = ft_substr(s, i, len);
			i += len;
		}
		j++;
	}
	return (arr);
}
