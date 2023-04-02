/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 08:53:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/02 18:03:34 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

/* Joins together n strings */
char	*ft_strnjoin(ssize_t n, ...)
{
	int		i;
	char	*tmp;
	char	*ret;

	va_list(strs);
	va_start(strs, n);
	i = 0;
	ret = NULL;
	while (i++ < n)
	{
		if (!ret)
		{
			ret = ft_strdup(va_arg (strs, char *));
			continue ;
		}
		tmp = ret;
		if (!tmp)
			return (NULL);
		ret = ft_strjoin(ret, va_arg(strs, char *));
		free(tmp);
	}
	va_end(strs);
	return (ret);
}
