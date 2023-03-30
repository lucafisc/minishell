/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:41:38 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/30 10:53:58 by tfregni          ###   ########.fr       */
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

void	get_prompt(void)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("> ");
		add_history(cmd);
		printf("here main\n");
		lexer(cmd);
		free(cmd);
	}
}

/* Alternative version in builtins/cd.c */
int	throw_err()
{
	write(2, "Error\n", 6);
	return (1);
}

char **matrix_dup(char **matrix, int extra)
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

t_shell	*init(char ***env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = matrix_dup(env, 0);
	*env = shell->env;
	shell->path = ft_split(getenv("PATH"), ':');
	//ft_print_strarr(shell->path);
	return (shell);
}

void	free_shell(t_shell *shell)
{
	ft_free_str_arr(shell->path);
	rl_clear_history();
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
		return (throw_err());
	// init_signals();
	get_prompt();
	free_shell(shell);
}
