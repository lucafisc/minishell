/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:29 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 15:56:46 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, int len)
{
	int		i;
	char	*match;

	if (!*to_find)
		return (str);
	i = 0;
	while (*str && len > 0)
	{
		if (*str == to_find[i])
		{
			match = str;
			while (to_find[i] && len - i >= 0)
			{
				if (match[i] != to_find[i])
					break ;
				i++;
			}
		}
		if (!to_find[i])
			return (match);
		i = 0;
		str++;
		len--;
	}
	return (NULL);
}
