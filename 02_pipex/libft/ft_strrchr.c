/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:50:04 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 15:51:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	while (len >= 0)
	{
		if (c == str[len])
			return (&str[len]);
		len--;
	}
	return (NULL);
}
