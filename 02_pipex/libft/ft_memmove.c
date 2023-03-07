/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:25:00 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/29 19:47:28 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* A good case to test is when dst is one byte after src:
there's the risk that src would chase itself and copy the
first letter over and over again */
/* Basically if dst < src copy the mem left to right
if dst > src copy the mem right to left */
static void	*ft_rev_memcpy(void *dst, const void *src, size_t len)
{
	while (len >= sizeof(uintmax_t))
	{
		len -= sizeof(uintmax_t);
		*(uintmax_t *)(dst + len) = *(const uintmax_t *)(src + len);
	}
	while (len >= sizeof(unsigned int))
	{
		len -= sizeof(unsigned int);
		*(unsigned int *)(dst + len) = *(const unsigned int *)(src + len);
	}
	while (len > 0)
	{
		len--;
		*(unsigned char *)(dst + len) = *(const unsigned char *)(src + len);
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	else if (dst > src)
		return (ft_rev_memcpy(dst, src, len));
	return (dst);
}
