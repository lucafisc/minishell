/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:07:33 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/02 16:55:42 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Even when the char is NULL one char is counted 						*/
void	parse_char(va_list *args, t_arg *arg, char spec)
{
	char	c;

	if (spec == '%')
	{
		c = '%';
		(*arg).width = 0;
	}
	else
		c = va_arg(*args, int);
	(*arg).arg_len++;
	print_char(arg, c);
}

/* It wasn't enough to check the existance of str: had to check str[0]	*/
void	parse_text(va_list *args, t_arg *arg, char spec)
{
	char	*str;
	int		len;

	if (spec == 's')
	{
		str = va_arg(*args, char *);
		if (!str)
		{
			if ((*arg).dot && (*arg).precision < 6)
				str = "";
			else
				str = "(null)";
		}
		len = ft_strlen(str);
		if ((str[0]) && (*arg).dot && (*arg).precision < len)
			(*arg).arg_len = (*arg).precision;
		else
			(*arg).arg_len = len;
		print_str(arg, str);
	}
	else
		parse_char(args, arg, spec);
}
