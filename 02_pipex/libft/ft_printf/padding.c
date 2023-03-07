/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:48:18 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/01 11:44:38 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Performs a final balancing of the struct for internal consistence	*/
/* If 0 flag is active and no precision the width is handled as			*/
/* precision (because the precision is handled by the putnbr function)	*/
/* If the arg is right aligned the difference between precision and len	*/
/* is taken from width so that there's both a left space padding and the*/
/* precision 0 padding. This was a headache.							*/
void	check_zero_precision_width(t_arg *arg)
{
	if ((*arg).zero && (!(*arg).precision || \
	((*arg).precision == 1 && (*arg).plus_sign)))
	{
		(*arg).zero = 0;
		(*arg).precision += (*arg).width;
		if ((*arg).alternate)
			(*arg).precision -= 2;
		if ((*arg).negative || (*arg).plus_sign)
			(*arg).precision--;
		(*arg).width = 0;
	}
	if ((*arg).precision >= (*arg).width)
		(*arg).width = 0;
	if ((*arg).precision >= (*arg).arg_len && (*arg).negative \
	&& !(*arg).right_padded)
		(*arg).width--;
	if (((*arg).width >= (*arg).precision) && \
	((*arg).precision - (*arg).arg_len > 0) && !(*arg).right_padded)
		(*arg).width -= ((*arg).precision - (*arg).arg_len);
}

/* The pointer version of the previous function	*/
void	check_zero_precision_width_ptr(t_arg *arg)
{
	if ((*arg).right_padded)
		return ;
	if ((*arg).width > (*arg).precision && (*arg).precision > (*arg).arg_len)
	{
		(*arg).width -= ((*arg).precision - (*arg).arg_len);
	}
	if ((*arg).zero && (*arg).width > (*arg).arg_len)
	{
		(*arg).precision = (*arg).width - 2;
		(*arg).width = 0;
	}
}

/* I used to handle it increading arg_len but then after left padding	*/
/* the arg_len would be off and the precision 0 padding would be wrong	*/
/* Since the return value is a sum of arg_len and tot_len I could swap	*/
/* approach with no further problems									*/
void	space_padding(t_arg *arg)
{
	while ((*arg).width > (*arg).arg_len)
	{
		ft_putchar_fd(' ', 1);
		(*arg).width--;
		(*arg).tot_len++;
	}
}

/* Since it's mutually exclusive with precision can be handled	*/
/* increasing arg_len											*/
void	zero_padding(t_arg *arg)
{
	while ((*arg).width > (*arg).arg_len)
	{
		ft_putchar_fd('0', 1);
		(*arg).arg_len++;
	}
}
