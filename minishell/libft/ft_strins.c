/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:58:13 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/13 15:37:02 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_second_string(char *s2, char *ret, int idx, int *i)
{
	while (s2 && s2[*i - idx])
	{
		ret[*i] = s2[*i - idx];
		(*i)++;
	}
}

static void	copy_remainder(char *s1, char *ret, int len, int idx, int *i)
{
	while (s1[idx + len])
	{
		ret[*i] = s1[idx + len];
		(*i)++;
		len++;
	}
}

/* It inserts s2 in s1 at the index idx substitung len chars of s1 */
/* It doesn't free the arguments */
char	*ft_strins(char *s1, char *s2, int len, int idx)
{
	int		len_s1;
	char	*ret;
	int		i;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	ret = malloc(sizeof(*ret) * (len_s1 + ft_strlen(s2) - len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < idx)
		ret[i] = s1[i];
	if (s2)
		copy_second_string(s2, ret, idx, &i);
	copy_remainder(s1, ret, len, idx, &i);
	ret[i] = '\0';
	return (ret);
}

// /* It inserts s2 in s1 at the index idx substitung len chars of s1 */
// /* It doesn't free the arguments */
// char	*ft_strins(char *s1, char *s2, int len, int idx)
// {
// 	int		len_s1;
// 	char	*ret;
// 	int		i;

// 	if (!s1)
// 		return (NULL);
// 	len_s1 = ft_strlen(s1);
// 	ret = malloc(sizeof(*ret) * (len_s1 + ft_strlen(s2) - len + 1));
// 	if (!ret)
// 		return (NULL);
// 	i = -1;
// 	while (++i < idx)
// 		ret[i] = s1[i];
// 	while (s2 && s2[i - idx])
// 	{
// 		ret[i] = s2[i - idx];
// 		i++;
// 	}
// 	while (s1[idx + len])
// 	{
// 		ret[i] = s1[idx + len];
// 		i++;
// 		len++;
// 	}
// 	ret[i] = '\0';
// 	return (ret);
// }
