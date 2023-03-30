/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:46:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/30 18:01:46 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_echo works assuming a null terminated 2D array of args is given as input.
// if the option -n is enabled, the string "-n" should be at index 0 of this array
// it assumes the parser will interpret the arguments before

//in this case args[1] should equal "hello         hi":
// echo "hello         hi"
// hello         hi

//in this case args[1] should equal "hello" and args[2] should equal "hi":
// echo hello         hi
// hello hi

#include "../minishell.h"

void	ft_echo(char **args)
{
	t_bool	n;
	int		i;

	if (!args)
		return ;
	n = true;
	i = 0;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		i++;
		n = false;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n)
		printf("\n");
}

int	main(int ac, char **av)
{
	char **my_args = ft_split("-n hello", ' ');
	// ft_print_strarr(my_args);
	ft_echo(my_args);
}
