/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:56:44 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 17:59:35 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dgts(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	long	l_n;
	int		dgt;
	int		negative;

	negative = 0;
	l_n = n;
	dgt = count_dgts(l_n);
	nbr = malloc(sizeof(*nbr) * (dgt + 1));
	if (!nbr)
		return (NULL);
	nbr[dgt] = '\0';
	if (l_n < 0)
	{
		nbr[0] = '-';
		l_n *= -1;
		negative = 1;
	}
	while (--dgt >= negative)
	{
		nbr[dgt] = l_n % 10 + '0';
		l_n /= 10;
	}
	return (nbr);
}
