/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:19 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/24 13:52:53 by tfregni          ###   ########.fr       */
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

static char	*trim_new_line(char *input)
{
	char	*trimmed;

	trimmed = ft_strtrim(input, "\n");
	free(input);
	return (trimmed);
}

// void	exec_script(t_shell *s, int fd)
// {
// 	char	*input;
// 	int		i;

// 	i = 0;
// 	while (1)
// 	{
// 		input = get_next_line(fd);
// 		i++;
// 		printf("input: %s\n", input);
// 		if (!input)
// 			break ;
// 		if (!validate_line(&input))
// 			continue ;
// 		input = trim_new_line(input);
// 		if (!is_param(input))
// 		{
// 			s->lexer = lexer(input);
// 			s->cmd = parser(s->lexer);
// 			printf("fd: %d\n", fd);
// 			execute(s, s->cmd);
// 		}
// 		else
// 			s->params = env_append(s->params, input);
// 		free(input);
// 	}
// 	close(fd);
// 	exit(0);
// }

void	exec_script(t_shell *s, int fd)
{
	char	*input;
	int		i;

	i = 0;
	(void) s;
	while (1)
	{
		input = get_next_line(fd);
		i++;
		if (!input)
			break ;
		if (!validate_line(&input))
			continue ;
		input = trim_new_line(input);
		if (!is_param(input))
		{
			s->lexer = lexer(input);
			s->cmd = parser(s->lexer);
			execute(s, s->cmd);
		}
		else
			s->params = env_append(s->params, input);
		free(input);
	}
	close(fd);
	exit(0);
}
// void	exec_script(t_shell *s, int fd)
// {
// 	char	*input;
// 	int		i;
// 	char	*trimmed;

// 	i = 0;
// 	while (1)
// 	{
// 		input = get_next_line(fd);
// 		i++;
// 		if (!input)
// 			break ;
// 		if (!validate_line(input))
// 			continue ;
// 		trimmed = ft_strtrim(input, "\n");
// 		if (!is_param(trimmed))
// 		{
// 			s->lexer = lexer(trimmed);
// 			s->cmd = parser(s->lexer);
// 			execute(s, s->cmd);
// 		}
// 		else
// 			s->params = env_append(s->params, trimmed);
// 		free(input);
// 		free(trimmed);
// 	}
// 	close(fd);
// 	exit(0);
// }
