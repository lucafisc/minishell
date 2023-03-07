/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:21:54 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 17:21:55 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dest;

	len = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(*dest) * (len + 1));
	if (dest)
	{
		dest[len] = '\0';
		len--;
		while (len >= 0)
		{
			dest[len] = src[len];
			len--;
		}
		return (dest);
	}
	return (NULL);
}
