/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:57:13 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/25 19:37:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(va_list *args, char spec)
{
	char	*str;

	(void) str;
	if (spec == 's')
	{
		str = va_arg(*args, char *);
		if (str)
		{
			ft_putstr_fd(str, 1);
			return (ft_strlen(str));
		}
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
	{
		ft_putchar_fd(va_arg(*args, int), 1);
		return (1);
	}
}
