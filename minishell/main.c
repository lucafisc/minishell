/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:41:38 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/04 18:06:15 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

void	free_shell(t_shell *shell)
{
	free(shell->prompt);
	ft_free_str_arr(shell->env);
	ft_free_str_arr(shell->params);
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

/* Since getenv will not work anyway maybe we don't
need the real env to point to our duplicated one */
void	init(char ***env)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return ;
	g_shell->env = matrix_dup(*env, 0);
	*env = g_shell->env;
	g_shell->user = get_username(g_shell);
	g_shell->exit = false;
	g_shell->pipe = false;
	init_builtins(g_shell);
	g_shell->params = NULL;
	g_shell->status = 0;
	g_shell->forked = false;
	g_shell->pids = NULL;
	add_status(0);
}

int	main(int ac, char *av[], char *env[])
{
	int		fd;

	init(&env);
	if (!g_shell)
		return (throw_err("init", NULL));
	init_signal();
	if (ac > 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			throw_err("minishell", av[1]);
			exit(127);
		}
		exec_script(g_shell, fd);
	}
	get_prompt(g_shell);
	free_shell(g_shell);
}
