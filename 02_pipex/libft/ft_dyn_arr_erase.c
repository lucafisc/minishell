/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dyn_arr_erase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:01:09 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/30 20:01:35 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * iterate over the underlying array while freeing and skipping all `item`s (j)
 * and move the strings that are not equal to `item` to their corresponding
 * position (i)
 */
void	iter_items(t_dyn_arr *dyn_arr, char *item, size_t *i)
{
	size_t	j;

	j = 0;
	while (j < dyn_arr->len)
	{
		if (!ft_strcmp(dyn_arr->ptr[j], item))
		{
			while (j < dyn_arr->len && !ft_strcmp(dyn_arr->ptr[j], item))
			{
				free(dyn_arr->ptr[j]);
				dyn_arr->ptr[j] = NULL;
				j++;
			}
		}
		if (j >= dyn_arr->len)
			break ;
		dyn_arr->ptr[*i] = dyn_arr->ptr[j];
		j++;
		(*i)++;
	}
}

/*
 * erase an item from dynamic array
 * modifies `len` and leaves `cap` unchanged
 */
void	ft_dyn_arrerase(t_dyn_arr *dyn_arr, char *item)
{
	size_t	i;
	size_t	new_len;

	if (!dyn_arr || !item || !*item)
		return ;
	i = 0;
	iter_items(dyn_arr, item, &i);
	new_len = i;
	while (i < dyn_arr->len)
		dyn_arr->ptr[i++] = NULL;
	dyn_arr->len = new_len;
}
