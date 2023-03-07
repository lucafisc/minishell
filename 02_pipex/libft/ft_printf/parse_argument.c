/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:17:30 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/01 11:44:47 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Initializing plus_sign to 0 so that if either	*/
/* space or + flag is triggered the field exists	*/
/* and carries the chosen symbol					*/
/* The dot property is needed otherwise %.s would	*/
/* print a whole string since precision is 0		*/
void	init_struc(t_arg *arg)
{
	(*arg).negative = 0;
	(*arg).dot = 0;
	(*arg).precision = 0;
	(*arg).null_prec = 0;
	(*arg).width = 0;
	(*arg).blank = 0;
	(*arg).alternate = 0;
	(*arg).zero = 0;
	(*arg).right_padded = 0;
	(*arg).plus_sign = 0;
	(*arg).arg_len = 0;
	(*arg).tot_len = 0;
}

/* Going through all flags, then width, then precision 	*/
/* Updating the struct in the process 					*/
/* The ret_value of printf is tot_len + arg_len			*/
/* Having two variables allows me to handle better the	*/
/* paddings, trading width or precision for arg_len when*/
/* needed 												*/
void	parse_arg(va_list *args, char **fmt, int *count)
{
	t_arg	arg;

	init_struc(&arg);
	arg.tot_len = *count;
	while (ft_strchr("-0# +", **fmt))
	{
		parse_flag(&arg, *fmt);
		(*fmt)++;
	}
	if (ft_isdigit(**fmt))
		parse_width(&arg, fmt);
	if (**fmt == '.')
		parse_precision(&arg, fmt);
	parse_specifier(args, &arg, **fmt);
	*count = arg.tot_len + arg.arg_len;
}
