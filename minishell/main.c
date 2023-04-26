/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:41:38 by tfregni           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/24 14:52:01 by lde-ross         ###   ########.fr       */
=======
/*   Updated: 2023/04/24 15:48:31 by tfregni          ###   ########.fr       */
>>>>>>> tim
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

void	free_shell(t_shell *shell)
{
	ft_free_str_arr(shell->path);
	free(shell->prompt);
	ft_free_str_arr(shell->env);
	ft_free_str_arr(shell->params);
	//rl_clear_history();
	/* free(shell->lexer)*/
	/* free(shell->parser)*/
	free_builtins(shell->builtins);
	free(shell);
}

char	*get_username(t_shell *s)
{
	char	*usr;

	(void) s;
	usr = getenv("USER");
	if (!usr)
		ft_strlcpy(usr, "guest", 6);
	return (usr);
}

/* more elaborate version of throw error */
int	throw_err(char *str, char *arg)
{
	if (str && str[0])
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	if (arg && arg[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	write(2, "\n", 1);
	return (1);
}

char	**matrix_dup(char **matrix, int extra)
{
	int		len;
	char	**new;
	int		i;

	len = ft_arrlen(matrix);
	new = malloc(sizeof(char *) * (len + 1 + extra));
	if (!new)
		return (NULL);
	i = 0;
	new[len] = NULL;
	while (matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		i++;
	}
	return (new);
}

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

// int	init_params(t_shell *s)
// {
// 	s->params = malloc(sizeof(char *));
// 	if (s->params)
// 	{
// 		s->params[0] = NULL;
// 		return (1);
// 	}
// 	return (0);
// }

/* Since getenv will not work anyway maybe we don't
need the real env to point to our duplicated one */
t_shell	*init(char ***env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = matrix_dup(*env, 0);
	*env = shell->env;
	shell->path = ft_split(getenv("PATH"), ':');
	shell->user = get_username(shell);
	shell->exit = false;
	shell->pipe = false;
	init_builtins(shell);
	shell->params = NULL;
	shell->status = 0;
<<<<<<< HEAD
	shell->forked = false;
	//ft_print_strarr(shell->path);
=======
>>>>>>> tim
	return (shell);
}

void	get_prompt(t_shell *s)
{
	char		*input;
	int			i = 0;

	while (i == 0)
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
			add_history(input);
			if (!is_param(input))
			{
				s->lexer = lexer(input);
				s->cmd = parser(s->lexer);
				execute(s, s->cmd);
			}
			else
				s->params = env_append(s->params, input);
			free(s->prompt);
			free(input);
		}
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;
	int		fd;

	shell = init(&env);
	if (!shell)
		return (throw_err("init", NULL));
	g_shell = shell;
	init_signal();
	if (ac > 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			throw_err("minishell", av[1]);
			exit(127);
		}
		exec_script(shell, fd);
	}
	get_prompt(shell);
	free_shell(shell);
}
