/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/23 17:46:23 by tfregni          ###   ########.fr       */
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

void	ft_export_replace(char **env, char *var, int index)
{
	free(env[index]);
	env[index] = ft_strdup(var);
}

void	ft_export_append(char ***env, char *var)
{
	char	**new_env;

	new_env = env_append(*env, var);
	*env = new_env;
}

/* Checks if input is a parameter */
/* https://pubs.opengroup.org/onlinepubs/009695399/utilities
/xcu_chap02.html#tag_02_05_02 */
/* A param should have =, not start with a digit and not have
any of the special chars macroed in SP_PARAM */
/* Compare to t_bool is_export_valid(char *var) in export.c */
static t_bool	is_param(char *input)
{
	int	i;

	i = -1;
	if (!ft_strchr(input, '=') || ft_isdigit(*input))
		return (false);
	while (input[++i])
	{
		if (ft_strchr(SP_PARAM, input[i]) || ft_is_space(input[i]))
			return (false);
	}
	return (true);
}

/* Export will set the variable also in the shell->params so that
the expander can always get the latest occurrence */
/* export AR_=bla doesn't throw an error but doesn't set the var */
/* It should be a valid one: check is_param in main.c */
void	ft_export(t_shell *s, t_command *c)
{
	int		var_index;
	char	*var;

	if (!c || !s || !c->cmd || !c->cmd[0] || !c->cmd[1])
		return ;
	var = c->cmd[1];
	if (!is_param(var))
	{
		ft_putstr_fd("minishell: export: not a valid identifier: ", 2);
		ft_putendl_fd(var, 2);
		return ;
	}
	s->params = env_append(s->params, var);
	var_index = search_array(s->env, var);
	if (var_index >= 0)
		ft_export_replace(s->env, var, var_index);
	else
		ft_export_append(&s->env, var);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void) ac;
// 	(void) av;
// 	t_shell *s = malloc(sizeof(t_shell));
// 	t_command *c = malloc(sizeof(t_command));
// 	c->cmd = malloc(sizeof(*c->cmd) * 3);
// 	for (int i = 0; i < 2; i++)
// 		c->cmd[i] = malloc(sizeof(char) * 100);
// 	ft_strlcpy(c->cmd[0], "export", 3);
// 	if (ac > 1)
// 		ft_strlcpy(c->cmd[1], av[1], ft_strlen(av[1]) + 1);
// 	else
// 		ft_strlcpy(c->cmd[1], "TRYME=bla", 10);
// 	c->cmd[2] = NULL;
// 	s->env = env_dup(env);
// 	ft_export(s, c);
// 	char *key =  ft_strtrunc(c->cmd[1], "=");
// 	printf("%s: %s\n", c->cmd[1], ft_getenv(key));
// 	free(key);
// 	ft_free_str_arr(c->cmd);
// 	ft_free_str_arr(s->env);
// 	free(s);
// 	free(c);
// }
