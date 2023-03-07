/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dyn_arr_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:00:02 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/31 18:51:11 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * free dynamic memory allocated for a dynamic array
 */
void	ft_dyn_arr_clear(t_dyn_arr *dyn_arr)
{
	size_t	i;

	i = 0;
	while (i < dyn_arr->len)
		free(dyn_arr->ptr[i++]);
	free(dyn_arr->ptr);
	free(dyn_arr);
}
