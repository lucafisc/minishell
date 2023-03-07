/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dyn_arr_pushback.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:57:39 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/31 09:54:25 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * calculate capacity for the new underlying array (when the dyn_arr->ptr
 * in use cannot fit the new element)
 */
static size_t	cap_calc(size_t cap)
{
	if (cap == 0)
		cap = 1;
	else if (cap < 1024)
		cap *= 2;
	else
		cap += (1048576 / cap + 1);
	return (cap);
}

/*
 * copy first `len` items of `m2` into `m1`
 */
static void	array_copy(char **m1, char **m2, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		m1[i] = m2[i];
		i++;
	}
}

/*
 * push an item to the end of a dynamic array and expand the underlying array
 * if necessary
 */
void	ft_dyn_arr_pushback(t_dyn_arr *dyn_arr, char *item)
{
	size_t	new_cap;
	char	**new_ptr;

	if (!dyn_arr)
		return ;
	if (dyn_arr->cap - dyn_arr->len <= 1)
	{
		if (dyn_arr->cap > dyn_arr->cap + 1)
			return ;
		new_cap = cap_calc(dyn_arr->cap);
		new_ptr = ft_calloc(new_cap, sizeof(char *));
		if (!new_ptr)
			return ;
		array_copy(new_ptr, dyn_arr->ptr, dyn_arr->len);
		free(dyn_arr->ptr);
		dyn_arr->ptr = new_ptr;
		dyn_arr->cap = new_cap;
	}
	dyn_arr->ptr[dyn_arr->len] = item;
	dyn_arr->len++;
}
