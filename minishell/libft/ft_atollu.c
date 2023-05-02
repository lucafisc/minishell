/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atollu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:51:44 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/01 20:15:49 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	ft_atollu(const char *str)
{
	uint64_t		nb;

	if (!str)
		return (0);
	while (ft_is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	nb = 0;
	while (ft_isdigit(*str))
		nb = nb * 10 + (*(str++) - '0');
	return (nb);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	if (ac < 2 || ac > 3)
// 		return (1);
// 	printf("You typed %llu\n", ft_atollu(av[1]));
// 	if (ft_atollu("9223372036854775808") > 9223372036854775807)
// 		printf("Larger than 9223372036854775807\n");
// 	printf("MAX_LL: %llu\n", __LONG_LONG_MAX__);
// }
