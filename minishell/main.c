/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:41:38 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/04 18:20:49 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	lexer(char *str)
// {
// 	int	i;
// 	int state;

// 	state = IN_NORMAL;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == S_QUOTE)
// 			printf("found S_QUOTE\n");
// 		else if (str[i] == D_QUOTE)
// 			printf("found D_QUOTE\n");
// 		i++;
// 	}
// }

void	get_prompt(t_shell *s)
{
	char	*cmd;

	while (1)
	{
		cmd = readline(s->prompt);
		// rl_on_new_line();
		// rl_redisplay();
		if (*cmd)
		{
			add_history(cmd);
			lexer(s, cmd);
			// write(1, "done\n", 5);
			free(cmd);
		}
	}
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
	ft_strdup(current);
	if (ft_strnstr(getcwd(NULL, 0), home, ft_strlen(home)))
	{
		tmp = current;
		current += ft_strlen(home);
		current = ft_strjoin("~", current);
		free(tmp);
	}
	printf("%s\n", current);
	return (current);
}

char	*create_prompt(t_shell *s)
{
	char	*tmp;
	char	*prompt;

	tmp = create_cwd(s);
	prompt = ft_strnjoin(7, RED, s->user, YELLOW, "@minishell ", DEFAULT, tmp, " > ");
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
	shell->prompt = create_prompt(shell);
	//ft_print_strarr(shell->path);
	return (shell);
}

void	free_shell(t_shell *shell)
{
	ft_free_str_arr(shell->path);
	free(shell->prompt);
	//rl_clear_history();
	/* free(shell->lexer)*/
	/* free(shell->parser)*/
	free(shell);
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	shell = init(&env);
	if (!shell)
		return (throw_err("init", NULL));
	init_signal();
	get_prompt(shell);
	free_shell(shell);
}
