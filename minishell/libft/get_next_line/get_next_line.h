/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:20:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/01/21 10:28:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

// char	*get_next_line(int fd);
// char	*ft_strchr(char const *str, char c);
// char	*ft_strdup(const char *src);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// size_t	ft_strlen(const char *str);

#endif
