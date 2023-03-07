/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:51:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/02 15:52:15 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Adding 2 to the arg_len because "0x" in included in it */
void	parse_ptr(va_list *args, t_arg *arg)
{
	uint64_t	ptr;

	ptr = va_arg(*args, uint64_t);
	if (ptr == 0)
	{
		(*arg).arg_len = 5;
		print_str(arg, "(nil)");
		return ;
	}
	count_figures(ptr, ft_strlen(SMALL_HEX), &(*arg).arg_len);
	check_zero_precision_width_ptr(arg);
	(*arg).arg_len += 2;
	print_ptr(ptr, arg);
}
