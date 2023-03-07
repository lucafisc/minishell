/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:01:48 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/26 20:12:47 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putptr_rec(uint64_t ptr, size_t base_len, char *base)
{
	if (ptr < base_len)
	{
		ft_putchar_fd(base[ptr % base_len], 1);
		return ;
	}
	putptr_rec(ptr / base_len, base_len, base);
	ft_putchar_fd(base[ptr % base_len], 1);
}

/* The precision 0 padding uses arg_len - 2 because precision	*/
/* refers to the part of number after 0x in pointers			*/
/* 0x is always printed also for 0 (unlike the hex conversion)	*/
void	putptr(uint64_t ptr, t_arg *arg)
{
	char	*base;
	size_t	base_len;

	(void) arg;
	base = SMALL_HEX;
	base_len = ft_strlen(base);
	ft_putstr_fd("0x", 1);
	while ((*arg).precision > (*arg).arg_len - 2)
	{
		ft_putchar_fd('0', 1);
		(*arg).arg_len++;
	}
	putptr_rec(ptr, base_len, base);
}

void	print_ptr(uint64_t ptr, t_arg *arg)
{
	if ((*arg).right_padded)
	{
		putptr(ptr, arg);
		space_padding(arg);
	}
	else
	{
		if ((*arg).zero)
			zero_padding(arg);
		space_padding(arg);
		putptr(ptr, arg);
	}
}
