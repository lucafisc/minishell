/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:39:56 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/01 11:37:45 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#ifdef DEBUG

void	print_struct(t_arg arg)
{
	printf("neg: %d\n", arg.negative);
	printf("dot: %d\n", arg.dot);
	printf("prec: %d\n", arg.precision);
	printf("null_prec: %d\n", arg.null_prec);
	printf("width: %d\n", arg.width);
	printf("blank: %d\n", arg.blank);
	printf("alt: %d\n", arg.alternate);
	printf("zero: %d\n", arg.zero);
	printf("right: %d\n", arg.right_padded);
	printf("plus: %c\n", arg.plus_sign);
	printf("arg_len: %d\n", arg.arg_len);
	printf("tot_len: %d\n", arg.tot_len);
}
#endif

/********************************************/
/* Conversions to handle: cspdiuxX% 		*/
/* BONUS 									*/
/* Combinations of '-0.' and flags '# +' 	*/
/********************************************/
int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	*fmt;
	int		ret_val;

	ret_val = 0;
	fmt = (char *)str;
	va_start(args, str);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			parse_arg(&args, &fmt, &ret_val);
		}
		else
		{
			ft_putchar_fd(*fmt, 1);
			ret_val++;
		}
		fmt++;
	}
	va_end(args);
	return (ret_val);
}
