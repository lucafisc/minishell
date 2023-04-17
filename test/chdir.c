/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:23:53 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/10 10:59:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*path;

	if (ac > 1)
	{
		if (chdir(av[1]) < 0)
			printf("Error\n");
	}
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
