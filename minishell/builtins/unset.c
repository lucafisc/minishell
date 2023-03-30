/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:48:25 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/30 07:33:23 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// env_dup is also inside unset.c
// duplicated here for testing purposes.
char	**env_dup(char **env)
{
	int		len;
	char	**new;
	int		i;

	len = ft_arrlen(env);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	new[len] = NULL;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	return (new);
}

char	**env_remove(char **env, int index)
{
	int		len;
	char	**new;
	int		i;
	int		j;

	len = ft_arrlen(env);
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new[len] = NULL;
	ft_free_str_arr(env);
	return (new);
}

void	ft_unset_remove(char ***env, int index)
{
	char	**new_env;

	new_env = env_remove(*env, index);
	*env = new_env;
}

int	arg_index(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(char ***env, char *var)
{
	int		var_index;

	var_index = arg_index(*env, var);
	if (var_index >= 0)
		ft_unset_remove(env, var_index);
	return ;
}

int	main(int ac, char **av, char **environ)
{
	(void) ac;
	(void) av;
	environ = env_dup(environ);
	ft_unset(&environ, "TERM_PROGRAM");
	ft_print_strarr(environ);
	ft_free_str_arr(environ);
}
