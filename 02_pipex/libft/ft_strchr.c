/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:49:50 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 15:52:13 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, char c)
{
	while (*str)
	{
		if (c == *str)
			return ((char *)str);
		str++;
	}
	if (!c)
		return ((char *)str);
	return (NULL);
}
