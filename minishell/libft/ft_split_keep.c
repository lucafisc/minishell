/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:57:02 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/25 21:19:58 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int count_words_keep(char *s, char c)
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

size_t str_siz_keep(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && (s[i] != c))
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_skip_char(s, s[i], i);
		i++;
	}
	return (i);
}

char **ft_split_keep(char *s, char c)
{
	int words;
	char **arr;
	int i;
	int	j;
	int	len;

	printf("splitting by %c\n", c);
	if (!s)
		return (NULL);
	words = count_words_keep(s, c);
	printf("string:%s\n", s);
	printf("words: %d\n", words);
	//exit(1);
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
			if (s[i + 1] == c && c != '|')
			{
				arr[j] = ft_calloc(3, sizeof(char));
				arr[j][0] = c;
				arr[j][1] = c;
				i++;
				i++;
				j++;
			}
			else
			{
				arr[j] = ft_calloc(2, sizeof(char));
				arr[j][0] = c;
				i++;
				j++;
			}
		}
		else
		{
			len = str_siz_keep((s + i), c);
			arr[j] = ft_substr(s, i, len);
			j++;
			i += len;
		}
	}
	return (arr);
}
