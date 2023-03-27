/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:41:38 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/27 17:19:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(void)
{
	char	*cmd;
	int i = 2;

	while (i-- > 0)
	{
		cmd = readline("minishell://");
		add_history(cmd);

		printf("%s", cmd);
		free(cmd);
	}
}

int	throw_err()
{
	write(2, "Error\n", 6);
	return (1);
}

t_shell	*init(char *env[])
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env;
	shell->path = ft_split(getenv("PATH"), ':');
	ft_print_strarr(shell->path);
	return (shell);
}

void	free_shell(t_shell *shell)
{
	ft_free_str_arr(shell->path);
	rl_clear_history();
	free(shell);
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	shell = init(env);
	if (!shell)
		return (throw_err());
	get_prompt();
	free_shell(shell);
}
