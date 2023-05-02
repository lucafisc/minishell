#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_arr(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	arr_rem(char **arr, int index)
{
	int i = index;
	int len = 0;
	printf("Original array\n");
	print_arr(arr);
	while (arr[len])
		len++;
	while (i < len - 1)
	{
		printf("arr_rem: free %s\n", arr[i]);
		free(arr[i]);
		printf("arr_rem: dup %s to index %d\n", arr[i + 1], i);
		arr[i] = strdup(arr[i + 1]);
		printf("arr_rem: arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	free(arr[i]);
	arr[i] = NULL;
}

void	free_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("Free %s\n", arr[i]);
		free(arr[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	char **arr = calloc(sizeof(*arr), 5);
	arr[0] = strdup("1");
	arr[1] = strdup("2");
	arr[2] = strdup("3");
	arr[3] = strdup("4");
	arr_rem(arr, atoi(av[1]));
	printf("Modified arr\n");
	print_arr(arr);
	free_arr(arr);
	free(arr);
}
