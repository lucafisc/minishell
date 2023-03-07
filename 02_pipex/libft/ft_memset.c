/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:11:51 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/02 21:04:13 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int ch, size_t len)
{
	unsigned char	*char_addr;
	size_t			i;

	i = 0;
	char_addr = ptr;
	while (i < len)
	{
		char_addr[i] = ch;
		i++;
	}
	return (ptr);
}
