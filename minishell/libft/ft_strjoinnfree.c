/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:30:39 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/03 19:22:21 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinnfree(char *existing, char new)
{
	size_t	i;
	char	*new_str;

	if (!existing)
		existing = ft_calloc(1, sizeof(char));
	if (!new)
		return (NULL);
	new_str = ft_calloc((ft_strlen(existing) + 1 + 1), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (existing[++i])
		new_str[i] = existing[i];
	new_str[i] = new;
	free(existing);
	return (new_str);
}
