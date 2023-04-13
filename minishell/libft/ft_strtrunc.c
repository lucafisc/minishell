/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:39:11 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/10 12:39:35 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* It truncates s1 at the first occurrence of a char in set */
/* What's returned is freeable */
char	*ft_strtrunc(char *s1, char *set)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		return (NULL);
	ret = ft_strdup(s1);
	i = 0;
	while (set && s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				ret[i] = '\0';
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (ret);
}
