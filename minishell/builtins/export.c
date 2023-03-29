/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/29 19:19:11 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_changeenv(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "arg", 3))
		{
			char new_arg[] = "arg=changed";
			*env = new_arg;
		}
		env++;
	}
}

void	ft_mispoint(char ***env)
{
	char	**new;

	new = malloc(sizeof(*new) * 3);
	new[0] = ft_strdup("hello");
	new[1] = ft_strdup("world");
	new[2] = NULL;
	*env = new;
}
char **matrix_dup(char **matrix)
{
	int		len;
	char	**new;
	int		i;

	len = ft_arrlen(matrix);
	new = malloc(sizeof(char *) * (len + 1));
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

char **matrix_append(char **matrix, char *var)
{
	int		len;
	char	**new;
	int		i;

	len = ft_arrlen(matrix);
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		i++;
	}
	matrix[i] = ft_strdup(var);
	new[len + 1] = NULL;
	ft_free_str_arr(matrix);
	return (new);	
}

int	search_array(char **env, char *var)
{
	int		i;
	int		len_eq;

	i = 0;
	len_eq = 0;
	while (var[len_eq] && var[len_eq] != '=')
	{
		len_eq++;
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len_eq))
			return (i);
		i++;
	}
	return (-1);
}


t_bool is_export_valid(char *var)
{
	while (*var && *var != '=')
	{
		if (ft_is_space(*var))
			return (false);
		var++;
	}
	if (!*var)
		return (false);
	return (true);
}

void	ft_export_replace(char **env, char *var, int index)
{
	free(env[index]);
	env[index] = ft_strdup(var);
}

void	ft_export_append(char ***env, char *var)
{
	char **new_env;

	new_env = matrix_append(*env, var);
	*env = new_env;	
}

void	ft_export(char ***env, char *var)
{
	int		var_index;

	if (!is_export_valid(var))
		return ;
	var_index = search_array(*env, var);
	printf("%d \n", var_index);
	if (var_index >= 0)
		ft_export_replace(*env, var, var_index);
	else
		ft_export_append(env, var);
}


int	main(int ac, char **av, char **environ)
{
	(void) ac;
	(void) av;

	environ = matrix_dup(environ);
	// ft_pwd();
	// ft_env(environ);
	// ft_changeenv(environ);
	// printf("------------------------\n");
	// ft_env(environ);
	// ft_mispoint(&environ);

	// char **new_env;
	// new_env = matrix_dup(environ);
	ft_export(&environ, "SPACESHIP_VERSION=hi");
	ft_print_strarr(environ);
	// ft_env(environ);
	
	ft_free_str_arr(environ);

}
