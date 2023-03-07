/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:09:33 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/01 11:54:38 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_rec_prec(uint64_t num, t_arg *arg, char *base, size_t base_len)
{
	if (num < base_len)
	{
		ft_putchar_fd(base[num % base_len], 1);
		return ;
	}
	putnbr_rec_prec(num / base_len, arg, base, base_len);
	ft_putchar_fd(base[num % base_len], 1);
}

/* Printing the appropriate 0x and trading arg_len for tot_len		*/
/* to keep the precision padding well adjusted						*/
void	check_sharp(uint64_t n, t_arg *arg, char *base)
{
	(void) n;
	if ((*arg).alternate)
	{
		if (ft_strchr(base, 'a'))
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
		(*arg).arg_len -= 2;
		(*arg).tot_len += 2;
		(*arg).width -= 2;
	}
}

/* Before the recursion handle signs (-, +, ' '), 0x for # flag,	*/
/* 0 number 0 prec and 0 padding for precision						*/
void	putnbr_base_precision(uint64_t num, t_arg *arg, char *base)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if ((*arg).negative)
		ft_putchar_fd('-', 1);
	else if (((*arg).plus_sign || (*arg).blank) && !(*arg).alternate)
		ft_putchar_fd((*arg).plus_sign, 1);
	if ((*arg).null_prec && num == 0)
		return ;
	else if ((*arg).alternate)
		check_sharp(num, arg, base);
	while ((*arg).precision > (*arg).arg_len - (*arg).negative)
	{
		(*arg).arg_len++;
		ft_putchar_fd('0', 1);
	}
	putnbr_rec_prec(num, arg, base, base_len);
}

/* Before padding check for # flag and account for the chars	*/
/* then get the right base, small or capital					*/
void	print_num_hex(uint64_t n, t_arg *arg, char spec)
{
	char	*base;

	if ((*arg).alternate && n != 0)
		(*arg).arg_len += 2;
	if (spec == 'x')
		base = SMALL_HEX;
	else
		base = CAPITAL_HEX;
	if ((*arg).right_padded)
	{
		putnbr_base_precision(n, arg, base);
		space_padding(arg);
	}
	else
	{
		if ((*arg).zero)
			zero_padding(arg);
		space_padding(arg);
		putnbr_base_precision(n, arg, base);
	}
}

/* Right padded = left aligned									*/
/* A number of cases is handled by the putnbr so that the issue	*/
/* boils down to "where" to be when I start writing the number	*/
/* Signs, precision, 0x are all part of the number and counted	*/
/* as arg_len in the struct so here it's just about left or		*/
/* right align and padding with 0 or space						*/
void	print_num_int(long n, t_arg *arg)
{
	if ((*arg).right_padded)
	{
		putnbr_base_precision(n, arg, BASE_10);
		space_padding(arg);
	}
	else
	{
		if ((*arg).zero)
			zero_padding(arg);
		space_padding(arg);
		putnbr_base_precision(n, arg, BASE_10);
	}
}
