/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/03 18:47:23 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_bool	is_param_name(char *input)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (ft_strchr(SP_PARAM, input[i]))
		{
			ft_error("minishell: export", \
				"not a valid identifier", input, 1);
			return (false);
		}
	}
	return (true);
}

/* Checks if input is a parameter */
/* https://pubs.opengroup.org/onlinepubs/009695399/utilities
/xcu_chap02.html#tag_02_05_02 */
/* A param should not start with a digit and not have
any of the special chars macroed in SP_PARAM. If it has a =
it's valid to write or retrieve */
t_bool	is_param(char *input)
{
	int		i;

	i = -1;
	if (!ft_strchr(input, '=') || ft_isdigit(*input) || *input == '=')
		return (false);
	while (++i <= (ft_strchr(input, '=') - input))
	{
		if (ft_strchr(SP_PARAM, input[i]))
			return (false);
	}
	while (input[i])
	{
		if (input[i] && ft_strchr(QUOTES, input[i]))
			i = ft_skip_char(input, input[i], i);
		else if (input[i] && input[i] == '!' && input[i + 1])
		{
			ft_error("minishell", "event not found", input + i, 1);
			return (false);
		}
		i++;
	}
	return (true);
}

/* Export will set the variable also in the shell->params so that
the expander can always get the latest occurrence */
/* From the manual: When no arguments are given, the results are unspecified. */
void	ft_export(t_shell *s, t_command *c)
{
	int		var_index;
	char	*var;

	if (!c || !s || !c->cmd || !c->cmd[0] || !c->cmd[1])
		return ;
	var = c->cmd[1];
	if (!is_param_name(var))
		return ;
	if (is_param(var) && c->outfile == 1)
	{
		s->params = env_append(s->params, var);
		var_index = search_array(s->env, var);
		if (var_index >= 0)
			ft_export_replace(s->env, var, var_index);
		else
			ft_export_append(&s->env, var);
	}
}
