/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:27 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/29 22:53:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	next_char(unsigned int i, char *s)
// {
// 	(void) i;
// 	*s += 1;
// }

// #include <stdio.h>
// int	main(void)
// {
// 	char	str[6] = "abcde";

// 	ft_striteri(str, next_char);
// 	printf("%s", str);
// }
