/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:07:46 by lde-ross          #+#    #+#             */
/*   Updated: 2023/05/03 20:33:01 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_cwd(t_shell *s)
{
	char	*current;
	char	*home;
	char	*tmp;

	(void) s;
	home = getenv("HOME");
	if (!home)
		return (ft_strdup(""));
	current = getcwd(NULL, 0);
	if (!current)
	{
		chdir("/");
		current = getcwd(NULL, 0);
	}
	if (ft_strnstr(current, home, ft_strlen(home)))
	{
		tmp = current;
		current += ft_strlen(home);
		current = ft_strjoin("~", current);
		free(tmp);
	}
	return (current);
}

char	*create_prompt(t_shell *s)
{
	char	*tmp;
	char	*prompt;

	tmp = create_cwd(s);
	prompt = ft_strnjoin(7, BLUE, s->user, YELLOW, "@minishell ", \
						DEFAULT, tmp, "> ");
	free(tmp);
	return (prompt);
}

void	prompt_routine(t_shell *s, char	*input)
{
	add_history(input);
	s->lexer = lexer(input);
	if (s->lexer)
	{
		s->cmd = parser(s->lexer);
		execute(s, s->cmd);
	}
	free(s->prompt);
	ft_free_str_arr(g_shell->path);
	free(input);
}

void	get_prompt(t_shell *s)
{
	char		*input;

	while (true)
	{
		s->prompt = create_prompt(s);
		input = readline(s->prompt);
		if (input == NULL)
		{
			free_shell(s);
			exit(1);
		}
		if (*input)
		{
			prompt_routine(s, input);
			g_shell->path = ft_split(ft_getenv("PATH"), ':');
		}
	}
}
