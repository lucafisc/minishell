/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:34 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/30 16:18:18 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nbr)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*nbr))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	while (ft_isdigit(*nbr))
	{
		result = result * 10 + (*nbr - '0');
		nbr++;
	}
	return ((int)(sign * result));
}

/* Hard coded the work around for > MAX_INT and < MIN_INT
Now it works for -99999999999999999999999999 for example
but not for -21474836488 while before the hard code did.
Is there a more elegant solution? */
// int	ft_atoi(const char *nbr)
// {
// 	long long	result;
// 	int			sign;

// 	result = 0;
// 	sign = 1;
// 	while (ft_isspace(*nbr))
// 		nbr++;
// 	if (*nbr == '+' || *nbr == '-')
// 	{
// 		if (*nbr == '-')
// 			sign *= -1;
// 		nbr++;
// 	}
// 	while (ft_isdigit(*nbr))
// 	{
// 		result = result * 10 + (*nbr - '0');
// 		nbr++;
//		// These lines were necessary to match the atoi func on Mac
// 		if ((result > 2147483647) && (sign == 1))
// 			return (-1);
// 		if ((result > 2147483648) && (sign == -1))
// 			return (0);
// 	}
// 	return ((int)(sign * result));
// }
