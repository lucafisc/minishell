/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:55:47 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/03 18:48:28 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	copy_word(const char *s, char **pt, int *i)
{
	while (s && *s)
	{
		(*pt)[*i] = *s;
		(*i)++;
		s++;
	}
}

char	*ft_strjoinchar(char const *s1, char const *s2, char c)
{
	int		len;
	char	*pt;
	int		i;

	if (!s1)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	pt = malloc(sizeof(char) * len);
	if (!pt)
		return (0);
	i = 0;
	copy_word(s1, &pt, &i);
	pt[i] = c;
	i++;
	copy_word(s2, &pt, &i);
	pt[i] = '\0';
	return (pt);
}
