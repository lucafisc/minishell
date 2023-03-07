/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/01 11:45:16 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* The flag ' ' activates the bool blank and sets		*/
/* ' ' as plus sign. Checking for '+' later guarantees	*/
/* the override											*/
void	parse_flag(t_arg *arg, char *flag)
{
	if (*flag == '-')
		(*arg).right_padded = 1;
	if (*flag == ' ')
	{
		(*arg).blank = 1;
		(*arg).plus_sign = ' ';
	}
	if (*flag == '#')
		(*arg).alternate = 1;
	if (*flag == '0')
		(*arg).zero = 1;
	if (*flag == '+')
		(*arg).plus_sign = '+';
}

/* I call this function when I'm at the first figure and I want	*/
/* to move forward so I need to use a double ptr				*/
void	parse_width(t_arg *arg, char **wdt)
{
	(*arg).width = ft_atoi(*wdt);
	while (ft_isdigit(**wdt))
		(*wdt)++;
}

/* If there's a precision flag the 0 flag is erased		*/
/* I need both the bool dot and the int precision to	*/
/* handle truncated strings correctly					*/
void	parse_precision(t_arg *arg, char **prec)
{
	(*arg).dot = 1;
	(*prec)++;
	(*arg).precision = ft_atoi(*prec);
	while (ft_isdigit(**prec))
		(*prec)++;
	if (!(*arg).precision)
		(*arg).null_prec = 1;
	if ((*arg).precision)
		(*arg).zero = 0;
}

/* This function handles the parser to call according to the type	*/
void	parse_specifier(va_list *args, t_arg *arg, char spec)
{
	if (ft_strchr("diuxX", spec))
		parse_num(args, arg, spec);
	else if (spec == 'p')
		parse_ptr(args, arg);
	else
		parse_text(args, arg, spec);
}
