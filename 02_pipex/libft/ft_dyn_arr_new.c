/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dyn_arr_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:54:06 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/30 19:55:36 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * initialize a new and empty dynamic array with a given capacity
 */
t_dyn_arr	*ft_dyn_arr_new(size_t cap)
{
	t_dyn_arr	*dyn_arr;
	char		**ptr;

	dyn_arr = ft_calloc(1, sizeof(t_dyn_arr));
	if (!dyn_arr)
		return (NULL);
	ptr = ft_calloc(cap, sizeof(char *));
	if (!ptr)
		return (NULL);
	dyn_arr->ptr = ptr;
	dyn_arr->len = 0;
	dyn_arr->cap = cap;
	return (dyn_arr);
}
