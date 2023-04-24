#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 1)
		return (printf("Gimme some to print!\n"));
	printf("Did you just say %s?\n", av[1]);
}
