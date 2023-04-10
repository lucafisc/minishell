/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/10 12:43:28 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /* test function to modify the environment */
// void ft_changeenv(char **env)
// {
// 	while (*env)
// 	{
// 		if (!ft_strncmp(*env, "arg", 3))
// 		{
// 			char new_arg[] = "arg=changed";
// 			*env = new_arg;
// 		}
// 		env++;
// 	}
// }

// /* test function to make the original env matrix
// pointing to a newly allocated one */
// void	ft_mispoint(char ***env)
// {
// 	char	**new;

// 	new = malloc(sizeof(*new) * 3);
// 	new[0] = ft_strdup("hello");
// 	new[1] = ft_strdup("world");
// 	new[2] = NULL;
// 	*env = new;
// }

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

t_bool	is_export_valid(char *var)
{
	while (*var && *var != '=')
	{
		if (ft_isdigit(var[0]) || ft_is_space(*var) || !ft_isalnum(*var))
			return (false);
		var++;
	}
	if (!*var)
		return (false);
	return (true);
}

static void	ft_export_replace(char **env, char *var, int index)
{
	free(env[index]);
	env[index] = ft_strdup(var);
}

static void	ft_export_append(char ***env, char *var)
{
	char	**new_env;

	new_env = env_append(*env, var);
	*env = new_env;
	//ft_print_strarr(new_env);
}

void	ft_export(t_shell *s, t_command *c)
{
	int		var_index;
	char	*var;

	if (!c || !s || !c->cmd || !c->cmd[0])
		return ;
	var = c->cmd[1];
	if (!is_export_valid(var))
		return ;
	var_index = search_array(s->env, var);
	if (var_index >= 0)
		ft_export_replace(s->env, var, var_index);
	else
		ft_export_append(&s->env, var);
}

/* Didn't think about many edge cases... */
char	*ft_getenv(char **env, char *key)
{
	int	len;
	int	i;

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

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_shell *s = malloc(sizeof(t_shell));
	t_command *c = malloc(sizeof(t_command));
	c->cmd = malloc(sizeof(*c->cmd) * 3);
	for (int i = 0; i < 2; i++)
		c->cmd[i] = malloc(sizeof(char) * 100);
	ft_strlcpy(c->cmd[0], "export", 3);
	if (ac > 1)
		ft_strlcpy(c->cmd[1], av[1], ft_strlen(av[1]) + 1);
	else
		ft_strlcpy(c->cmd[1], "TRYME=bla", 10);
	c->cmd[2] = NULL;
	s->env = env_dup(env);
	ft_export(s, c);
	char *key =  ft_strtrunc(c->cmd[1], "=");
	printf("%s: %s\n", c->cmd[1], ft_getenv(s->env, key));
	free(key);
	ft_free_str_arr(c->cmd);
	ft_free_str_arr(s->env);
	free(s);
	free(c);
}
