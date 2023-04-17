/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:38:34 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/17 11:28:35 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	*g_shell;

/* returns an allocated 0-terminated copy of the env */
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


/* given env matrix and a string, it appends the
string a returns the new matrix */
char	**env_append(char **env, char *var)
{
	int		len;
	char	**new;
	int		i;

	len = ft_arrlen(env);
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[len] = ft_strdup(var);
	new[len + 1] = NULL;
	ft_free_str_arr(env);
	return (new);
}

/* It returns the index num of the var entry in the
array or -1 if no match */
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

/* Didn't think about many edge cases... */
char	*ft_getenv(char *key)
{
	int		len;
	int		i;
	char	**env;

	env = g_shell->env;
	if (!env)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
