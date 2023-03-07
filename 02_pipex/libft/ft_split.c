/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:57:28 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/03 16:45:54 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	size_t	count;

	if (!s)
		return (0);
	if (!c)
		return (1);
	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		num_words;
	size_t	word;
	size_t	len;

	num_words = count_words(s, c);
	strs = malloc(sizeof(*strs) * (num_words + 1));
	if (!strs)
		return (NULL);
	word = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			strs[word++] = ft_substr(s, 0, len);
			s += len;
		}
	}
	strs[word] = 0;
	return (strs);
}
