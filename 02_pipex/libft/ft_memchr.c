/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:54:03 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 15:54:18 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Should test for size = 0 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*char_str;

	if (!n)
		return (NULL);
	i = 0;
	char_str = (unsigned char *)str;
	while (i < n)
	{
		if (char_str[i] == (unsigned char) c)
			return (&char_str[i]);
		i++;
	}
	return (NULL);
}
