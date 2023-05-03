/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:33:56 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/03 18:42:38 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	internal_export(t_shell *s, char *var)
{
	int	var_index;

	var_index = search_array(s->env, var);
	if (var_index >= 0)
		ft_export_replace(s->env, var, var_index);
	else
		ft_export_append(&s->env, var);
}

/* Given t_shell to retrieve the env and oldpwd it retrieves
current dir, updates env with OLDPWD and PWD. It does not free
oldpwd nor env */
void	update_pwd(t_shell *s, t_command *c, char *oldpwd)
{
	char	*tmp;
	char	*cwd;

	(void) c;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		throw_err("cd", cwd);
		free(cwd);
		return ;
	}
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	internal_export(s, tmp);
	free(tmp);
	tmp = ft_strjoin("PWD=", cwd);
	internal_export(s, tmp);
	free(tmp);
	free(cwd);
}

void	free_cd(char *path, char *oldpwd)
{
	free(path);
	free(oldpwd);
}

/* It sets the value of path expanding - or "" */
int	set_path(t_command *c, char **path)
{
	if (!c->cmd[1])
	{
		if (!ft_getenv("HOME"))
			return (1);
		*path = ft_strdup(ft_getenv("HOME"));
		c->cmd = env_append(c->cmd, *path);
	}
	else
	{
		if (!c->cmd[1][0])
			*path = ft_strdup(".");
		else if (!ft_strncmp(c->cmd[1], "-", 2))
			*path = ft_strdup(ft_getenv("OLDPWD"));
		else
			*path = ft_strdup(c->cmd[1]);
	}
	return (0);
}

void	ft_cd(t_shell *s, t_command *c)
{
	char	*oldpwd;
	char	*path;
	int		len;

	if (!s || !c || !c->cmd || !c->cmd[0])
		return ;
	len = ft_arrlen(c->cmd);
	if (len > 2)
		return (ft_error("minishell", "too many arguments", c->cmd[0], 1));
	if (set_path(c, &path) == 1)
		return ;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd || chdir(path) < 0)
	{
		ft_error("minishell: cd", path, strerror(errno), 1);
		free_cd(path, oldpwd);
		return ;
	}
	if (!ft_strncmp(c->cmd[1], "-", 2))
		ft_putendl_fd(path, 1);
	update_pwd(s, c, oldpwd);
	free_cd(path, oldpwd);
}
