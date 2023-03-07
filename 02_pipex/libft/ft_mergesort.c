/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:09:28 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/20 13:26:50 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG
# include <stdio.h>

void	print_array(int *arr, int len)
{
	int	i;

	i = 0;
	printf("\nsize: %d - \t", len);
	while (i < len)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}
#endif

static int	*create_subarr(int **arr, int start, int end)
{
	int	size;
	int	*sub;
	int	i;

	size = end - start + 1;
	sub = malloc(sizeof(*sub) * size);
	if (!sub)
		return (NULL);
	i = -1;
	while (++i <= end - start)
		sub[i] = (*arr)[start + i];
	return (sub);
}

static void	free_subarr(int **sub1, int **sub2)
{
	free(*sub1);
	sub1 = NULL;
	free(*sub2);
	sub2 = NULL;
}

static void	merge(int *arr, int start, int mid, int end)
{
	int	i;
	int	j;
	int	k;
	int	*sub1;
	int	*sub2;

	sub1 = create_subarr(&arr, start, mid);
	sub2 = create_subarr(&arr, (mid + 1), end);
	k = start;
	i = 0;
	j = 0;
	while (sub1 && sub2 && i < (mid - start + 1) && j < (end - mid))
	{
		if (sub1[i] < sub2[j])
			arr[k++] = sub1[i++];
		else
			arr[k++] = sub2[j++];
	}
	while (sub1 && sub2 && i < (mid - start + 1))
		arr[k++] = sub1[i++];
	while (sub1 && sub2 && j < (end - mid))
		arr[k++] = sub2[j++];
	free_subarr(&sub1, &sub2);
}

void	ft_mergesort(int *arr, int start, int end)
{
	int	mid;

	if (start >= end)
		return ;
	mid = (end + start) / 2;
	ft_mergesort(arr, start, mid);
	ft_mergesort(arr, mid + 1, end);
	merge(arr, start, mid, end);
}

// int	main(void)
// {
// 	// int	a[10] = {2, 7, 1, 9, -6, 8, -33, 23, 3, 4};
// 	int a[5] = {4, 2, 1, 3, 5};

// 	print_array(a, 5);
// 	ft_mergesort(a, 0, 4);
// 	print_array(a, 5);
// }
