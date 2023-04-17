/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:41:38 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/17 14:05:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

void	free_shell(t_shell *shell)
{
	ft_free_str_arr(shell->path);
	free(shell->prompt);
	ft_free_str_arr(shell->env);
	printf("freeeeeeee\n");
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
	prompt = ft_strnjoin(7, RED, s->user, YELLOW, "@minishell ", DEFAULT, tmp, "> ");
	free(tmp);
	return (prompt);
}

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
	init_builtins(shell);
	//ft_print_strarr(shell->path);
	return (shell);
}

void	get_prompt(t_shell *s)
{
	char		*input;
	int			i = 0;
	t_lexer		*lex_list;
	t_command	*par_list;

	while (i == 0)
	{
		s->prompt = create_prompt(s);
		input = readline(s->prompt);
		 if (input == NULL) {
            printf("EOF encountered. Exiting...\n");
			free(input);
			free_shell(s);
            exit(1);
        }
		if (*input)
		{
			add_history(input);
			lex_list = lexer(input);
			par_list = parser(lex_list);
			execute(s, par_list);
			free_prompt(input, &lex_list, &par_list);
			free(s->prompt);
		}
		free(s->prompt);
	}
}


int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	shell = init(&env);
	if (!shell)
		return (throw_err("init", NULL));
	g_shell = shell;
	init_signal();
	get_prompt(shell);
	free_shell(shell);
}
