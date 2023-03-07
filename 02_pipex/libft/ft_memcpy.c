/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:14:28 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/16 18:40:21 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* with NULL dst and src but n != 0 should return NULL */
/* with just NULL src it should segfault */
/* To improve performance I first try to use the CPU native width */
/* then I fall back to smaller and smaller chunks */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	if (!dst && !src && n)
		return (NULL);
	ret = dst;
	while (n >= sizeof(uintmax_t))
	{
		*(uintmax_t *)dst = *(uintmax_t *)src;
		dst += sizeof(uintmax_t);
		src += sizeof(uintmax_t);
		n -= sizeof(uintmax_t);
	}
	while (n >= sizeof(unsigned int))
	{
		*(unsigned int *)dst = *(unsigned int *)src;
		dst += sizeof(unsigned int);
		src += sizeof(unsigned int);
		n -= sizeof(unsigned int);
	}
	while (n > 0)
	{
		*(unsigned char *)dst++ = *(unsigned char *)src++;
		--n;
	}
	return (ret);
}

/* Old slower version*/
// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t	i;

// 	if (!dst && !src && n)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
// 		i++;
// 	}
// 	return (dst);
// }
