/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:08:53 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/02 15:24:07 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>

# ifdef DEBUG
#  include <stdio.h>
# endif

/* ************************************ */
/* negative: num < 0					*/
/* dot: a precision is indicated		*/
/* precision: . flag, actual int		*/
/* null_prec: if the prec is set to 0	*/
/* width: width							*/
/* blank: using space instead of +		*/
/* alternate: # flag for %x %X			*/
/* zero: 0 left padding					*/
/* right_padded: - flag					*/
/* plus_sign: + or space, empty if none	*/
/* arg_len: argument's length			*/
/* tot_len: total len including padding	*/
/* ************************************ */
typedef struct s_arg
{
	bool	negative;
	bool	dot;
	int		precision;
	bool	null_prec;
	int		width;
	bool	blank;
	int		alternate;
	bool	zero;
	bool	right_padded;
	char	plus_sign;
	int		arg_len;
	int		tot_len;
}				t_arg;

/* DEBUG */
void	print_struct(t_arg arg);

/* printf main functions */
int		ft_printf(const char *str, ...);
void	parse_arg(va_list *args, char **fmt, int *count);
void	parse_flag(t_arg *arg, char *flag);
void	parse_width(t_arg *arg, char **wdt);
void	parse_precision(t_arg *arg, char **prec);
void	parse_specifier(va_list *args, t_arg *arg, char spec);
void	parse_num(va_list *args, t_arg *arg, char spec);
void	parse_ptr(va_list *args, t_arg *arg);
void	parse_text(va_list *args, t_arg *arg, char spec);
void	print_char(t_arg *arg, char c);
void	print_str(t_arg *arg, char *str);
void	print_num_int(long n, t_arg *arg);
void	print_num_hex(uint64_t n, t_arg *arg, char spec);
void	print_ptr(uint64_t ptr, t_arg *arg);

/* printf specific helper functions */
int		count_figures(uint64_t n, size_t base_len, int *count);
void	putnbr_base_precision(uint64_t num, t_arg *arg, char *base);
void	zero_padding(t_arg *arg);
void	space_padding(t_arg *arg);
void	check_zero_precision_width(t_arg *arg);
void	check_zero_precision_width_ptr(t_arg *arg);

/* Libft functions */
int		ft_atoi(const char *nbr);
int		ft_isdigit(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strchr(char const *str, char c);
size_t	ft_strlen(const char *str);

# define SMALL_HEX "0123456789abcdef"
# define CAPITAL_HEX "0123456789ABCDEF"
# define BASE_10 "0123456789"
# ifndef INT_MAX
#  define INT_MAX 2147483647
#  define INT_MIN -2147483648
# endif

#endif
