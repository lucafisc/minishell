/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/04 12:55:39 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	print_stuff(char *str)
{
	return (printf("%s", str));
}

void	print_sum(int a, int b)
{
	printf("%d\n", a + b);
}

int	main(void)
{
	int		(*funcs[3])(char *);

	funcs[0] = print_stuff;
	/* I can't assign print_sum to funcs[1] because it expects
	to return an int and to have a char * arg */
	// funcs[1] = print_sum;
	funcs[2] = NULL;
	/* Function call */
	funcs[0] ("Hello world\n");
	// funcs[1] (4, 5);

	/* The workaround I thought is this: */
	// void	*funcs_void[3];
	// int		(*void_print_stuff)(char *);
	// void	(*void_print_sum)(int, int);
	// funcs_void[0] = void_print_stuff;
	// funcs_void[1] = void_print_sum;
	/* But I'm not able to call the function then */
	// funcs_void[0] ("Hello world\n");
}
