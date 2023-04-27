/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 08:53:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/27 02:00:52 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	strjoinchar_size(char **arr, int len)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < len)
	{
		size += ft_strlen(arr[i]);
		i++;
	}
	printf("size: %d\n", size + len - 1);
	return (size + len - 1);
}

static void	copy_word(char **dest, char *src)
{
	int	j;

	j = 0;
	while (src && src[j])
	{
		**dest = src[j];
		j++;
		(*dest)++;
	}
}

/* Given a NULL-terminated array of strings it joins them
separated by the given char. The return is freeable */
char	*ft_strnjoinchar(char **arr, char c)
{
	int		len;
	int		i;
	char	*ret;
	char	*cur;

	len = ft_arrlen(arr);
	ret = ft_calloc(strjoinchar_size(arr, len) + 1, sizeof(*ret));
	if (!ret)
		return (NULL);
	cur = ret;
	i = 0;
	while (i < len)
	{
		copy_word(&cur, arr[i]);
		if (i != len - 1)
			*cur++ = c;
		i++;
	}
	return (ret);
}

// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	char	**matrix;
// 	int		i;

// 	if (ac == 1)
// 		return (printf("Need args\n"));
// 	matrix = ft_calloc(sizeof(*matrix), ac + 1);
// 	i = -1;
// 	while (++i < ac - 1)
// 		matrix[i] = ft_strdup(av[i + 1]);
// 	char *join = ft_strnjoinchar(matrix, ' ');
// 	printf("%s\n", join);
// 	ft_free_str_arr(matrix);
// 	free(join);
// }
