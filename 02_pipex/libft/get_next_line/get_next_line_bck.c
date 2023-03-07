/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:33:28 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 19:42:16 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

static void	free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*save_mem(char **str_save)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	while ((*str_save)[i] && (*str_save)[i] != '\n')
		i++;
	tmp = *str_save;
	line = ft_substr(tmp, 0, i + 1);
	*str_save = ft_strdup(&(*str_save)[i + 1]);
	free_ptr(&tmp);
	return (line);
}

static int	read_data(int fd, char **buf, char **str_save)
{
	int		read_bytes;
	char	*tmp;

	read_bytes = 1;
	while (!ft_strchr(*str_save, '\n') && read_bytes)
	{
		read_bytes = read(fd, *buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (read_bytes);
		(*buf)[read_bytes] = '\0';
		tmp = *str_save;
		*str_save = ft_strjoin(tmp, *buf);
		free_ptr(&tmp);
	}
	return (read_bytes);
}

char	*extract_line(int fd, char **buf, char **str_save)
{
	int		read_bytes;
	char	*tmp;

	if (ft_strchr(*str_save, '\n'))
		return (save_mem(str_save));
	read_bytes = read_data(fd, buf, str_save);
	if (read_bytes < 0 || (read_bytes == 0 && !**str_save))
	{
		free_ptr(str_save);
		return (NULL);
	}
	if (ft_strchr(*str_save, '\n'))
		return (save_mem(str_save));
	if (!ft_strchr(*str_save, '\n') && **str_save)
	{
		tmp = ft_strdup(*str_save);
		free_ptr(str_save);
		return (tmp);
	}
	return (NULL);
}

/*
Returns a line read from the given fd or NULL. It has to be freed.
*/
char	*get_next_line(int fd)
{
	static char	*str_save[OPEN_MAX + 1];
	char		*buf;
	char		*line;



	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (!str_save[fd] )
		str_save[fd] = ft_strdup("");
	line = extract_line(fd, &buf, &str_save[fd]);
	free_ptr(&buf);
	return (line);
}
