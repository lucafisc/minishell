/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:19 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/29 13:07:33 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* It validates a line from a script to be processed
or not. If not, it frees the line */
static int	validate_line(char **input)
{
	if (**input == '\n' || **input == '#')
	{
		free(*input);
		return (0);
	}
	return (1);
}

/* It trims the \n char, frees the input and returns the trimmed*/
static char	*trim_new_line(char **input)
{
	char	*trimmed;

	trimmed = ft_strtrim(*input, "\n");
	free(*input);
	*input = trimmed;
	return (trimmed);
}

void	exec_script(t_shell *s, int fd)
{
	char	*input;
	int		i;

	i = 0;
	while (1)
	{
		input = get_next_line(fd);
		i++;
		if (!input)
			break ;
		if (!validate_line(&input))
			continue ;
		input = trim_new_line(&input);
		s->lexer = lexer(input);
		if (s->lexer)
		{
			s->cmd = parser(s->lexer);
			execute(s, s->cmd);
		}
		free(input);
	}
	close(fd);
	exit(0);
}
