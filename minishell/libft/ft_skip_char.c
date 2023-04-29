/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:19:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/29 11:53:09 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_skip_char(char *str, char c, int i)
{
	if (!str)
		return (i);
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
