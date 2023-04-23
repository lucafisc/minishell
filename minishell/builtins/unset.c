/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:48:25 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/22 00:13:14 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**env_remove(char **env, int index)
// {
// 	int		len;
// 	char	**new;
// 	int		i;
// 	int		j;

// 	len = ft_arrlen(env);
// 	new = malloc(sizeof(char *) * len);
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (env[i])
// 	{
// 		if (i != index)
// 		{
// 			new[j] = ft_strdup(env[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	new[len] = NULL;
// 	ft_free_str_arr(env);
// 	return (new);
// }

char	**env_remove(char **env, int index)
{
	int	i;
	int	len;

	if (!env || index < 0)
		return (env);
	i = index;
	len = ft_arrlen(env);
	while (i < len - 1)
	{
		free(env[i]);
		env[i] = ft_strdup(env[i + 1]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	ft_unset_remove(char ***env, int index)
{
	char	**new_env;

	new_env = env_remove(*env, index);
	*env = new_env;
}

// void	ft_unset(char ***env, char *var)
// {
// 	int		var_index;

// 	var_index = arg_index(*env, var);
// 	if (var_index >= 0)
// 		ft_unset_remove(env, var_index);
// 	return ;
// }

void	ft_unset(t_shell *s, t_command *c)
{
	int		var_index;
	char	*var;

	if (!s || !c || !c->cmd || !c->cmd[0])
	{
		throw_err("unset", NULL);
		return ;
	}
	if (!c->cmd[1])
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return ;
	}
	var = c->cmd[1];
	var_index = 1;
	while (var_index >= 0)
	{
		var_index = arg_index(s->params, var);
		ft_unset_remove(&(s->params), var_index);
	}
	var_index = arg_index(s->env, var);
	if (var_index >= 0)
		ft_unset_remove(&(s->env), var_index);
	return ;
}

// int	main(int ac, char **av, char **env)
// {
// 	t_shell *s = malloc(sizeof(t_shell));
// 	t_command *c = malloc(sizeof(t_command));
// 	c->cmd = malloc(sizeof(*c->cmd) * ac + 1);
// 	for (int i = 0; i < ac; i++)
// 		c->cmd[i] = malloc(sizeof(char) * 100);
// 	for (int j = 0; j < ac; j++)
// 		ft_strlcpy(c->cmd[j], av[j], ft_strlen(av[j]) + 1);
// 	c->cmd[ac] = NULL;
// 	s->env = env_dup(env);
// 	ft_unset(s, c);
// 	ft_print_strarr(s->env);
// 	ft_free_str_arr(c->cmd);
// 	ft_free_str_arr(s->env);
// 	free(s);
// 	free(c);
// }
