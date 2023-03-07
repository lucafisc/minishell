/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:57:37 by tfregni           #+#    #+#             */
/*   Updated: 2022/11/28 17:58:28 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		size;
	int		i;
	int		i_join;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	i_join = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(*join) * (size + 1));
	if (!join)
		return (NULL);
	while (s1[i])
		join[i_join++] = s1[i++];
	i = 0;
	while (s2[i])
		join[i_join++] = s2[i++];
	join[i_join] = '\0';
	return (join);
}
