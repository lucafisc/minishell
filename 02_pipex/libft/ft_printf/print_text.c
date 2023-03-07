/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:17:24 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/26 20:12:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_arg *arg, char c)
{
	if ((*arg).right_padded)
	{
		ft_putchar_fd(c, 1);
		space_padding(arg);
	}
	else
	{
		space_padding(arg);
		ft_putchar_fd(c, 1);
	}
}

/* Handling with write allows me to easily truncate strings	*/
/* The correct length is set while parsing the string in 	*/
/* the previous step										*/
void	print_str(t_arg *arg, char *str)
{
	if ((*arg).right_padded)
	{
		write(1, str, (*arg).arg_len);
		space_padding(arg);
	}
	else
	{
		space_padding(arg);
		write(1, str, (*arg).arg_len);
	}
}
