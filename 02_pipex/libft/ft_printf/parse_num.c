/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:52:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/01 11:48:43 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/* The parsing functions finalize the struct before printing.				  */
/* They calculate the argument size, adjust width, precision and zero to be	  */
/* internally consistent then call the appropriate print function			  */
/* ************************************************************************** */

/* Returns the size in chars of a given unsigned number in a given base		*/
int	count_figures(uint64_t n, size_t base_len, int *count)
{
	if (n < base_len)
		return (++(*count));
	count_figures(n / base_len, base_len, count);
	return (++(*count));
}

void	parse_hex(uint64_t n, t_arg *arg, char spec)
{
	count_figures(n, ft_strlen(SMALL_HEX), &(*arg).arg_len);
	if (n == 0)
		(*arg).alternate = 0;
	if ((*arg).null_prec)
	{
		(*arg).zero = 0;
		if (n == 0)
			(*arg).arg_len--;
	}
	check_zero_precision_width(arg);
	print_num_hex(n, arg, spec);
}

/* Saving the fact that the number is negative in the struct so that	*/
/* the putnbr func works just with uint									*/
/* Making space for the plus or the ' ' if the flags were activated		*/
/* Taking back space if .0 and num 0									*/
void	parse_int(long n, t_arg *arg)
{
	if (n < 0)
	{
		(*arg).negative = 1;
		(*arg).arg_len++;
		n = -n;
	}
	else if ((*arg).plus_sign)
	{
		(*arg).precision++;
		(*arg).arg_len++;
	}
	count_figures(n, ft_strlen(BASE_10), &(*arg).arg_len);
	if ((*arg).null_prec)
	{
		(*arg).zero = 0;
		if (n == 0)
			(*arg).arg_len--;
	}
	check_zero_precision_width(arg);
	print_num_int(n, arg);
}

/* If the uint is not to be printed as hex it can be handled like the ints	*/
/* In any case it shouldn't have sign flags so I deactivate them here		*/
void	parse_uint(uint32_t n, t_arg *arg, char spec)
{
	(*arg).plus_sign = 0;
	(*arg).blank = 0;
	if (spec == 'x' || spec == 'X')
		parse_hex(n, arg, spec);
	else
		parse_int(n, arg);
}

/* The first step: dividing ints (can be negative) from uints	*/
void	parse_num(va_list *args, t_arg *arg, char spec)
{
	long	n;

	n = 0;
	if (spec == 'd' || spec == 'i')
	{
		n = va_arg(*args, int);
		parse_int(n, arg);
	}
	else
	{
		n = va_arg(*args, uint32_t);
		parse_uint(n, arg, spec);
	}
}
