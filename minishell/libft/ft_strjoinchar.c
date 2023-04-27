/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:55:47 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 00:20:29 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	copy_word(const char *s, char **pt, int *i)
{
	// printf("%c\n", (*pt)[*i]);
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

	// ft_putstr_fd("here\n", 1);
	if (!s1)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	pt = malloc(sizeof(char) * len);
	if (!pt)
		return (0);
	i = 0;
	copy_word(s1, &pt, &i);
	// while (*s1)
	// {
	// 	pt[i] = *s1;
	// 	i++;
	// 	s1++;
	// }
	pt[i] = c;
	i++;
	copy_word(s2, &pt, &i);
	// while (s2 && *s2)
	// {
	// 	pt[i] = *s2;
	// 	i++;
	// 	s2++;
	// }
	pt[i] = '\0';
	printf("%s\n", pt);
	return (pt);
}
