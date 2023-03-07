/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:42:55 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/04 21:00:21 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Added check for the size to include the '\0'
size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	offset;

	offset = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (*(src + offset) && (offset < size - 1))
		{
			*(dest + offset) = *(src + offset);
			offset++;
		}
	}
	*(dest + offset) = '\0';
	while (*(src + offset) != '\0')
		offset++;
	return (offset);
}
