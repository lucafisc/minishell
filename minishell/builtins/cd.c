/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:33:56 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/30 14:44:14 by tfregni          ###   ########.fr       */
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
void	set_path(t_command *c, char **path)
{
	char	*trimmed;

	if (!c->cmd[1])
	{
		*path = ft_strdup(ft_getenv("HOME"));
		c->cmd = env_append(c->cmd, *path);
	}
	else
	{
		trimmed = trim_quotes(c->cmd[1]);
		free(c->cmd[1]);
		c->cmd[1] = trimmed;
		if (!c->cmd[1][0])
			*path = ft_strdup(".");
		else if (!ft_strncmp(c->cmd[1], "-", 2))
			*path = ft_strdup(ft_getenv("OLDPWD"));
		else
			*path = ft_strdup(c->cmd[1]);
	}
}

void	ft_cd(t_shell *s, t_command *c)
{
	char	*oldpwd;
	char	*path;

	if (!s || !c || !c->cmd || !c->cmd[0])
		return ;
	set_path(c, &path);
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

// int	main(int ac, char **av, char **env)
// {
// 	(void) ac;
// 	(void) av;
// 	t_shell *s = malloc(sizeof(t_shell));
// 	t_command *c = malloc(sizeof(t_command));
// 	c->cmd = malloc(sizeof(*c->cmd) * 3);
// 	for (int i = 0; i < 2; i++)
// 		c->cmd[i] = malloc(sizeof(char) * 100);
// 	ft_strlcpy(c->cmd[0], "cd", 3);
// 	if (ac > 1)
// 		ft_strlcpy(c->cmd[1], av[1], ft_strlen(av[1]) + 1);
// 	else
// 		ft_strlcpy(c->cmd[1], "/bin", 5);
// 	c->cmd[2] = NULL;
// 	s->env = env_dup(env);
// 	ft_cd(s, c);
// 	printf("PWD: %s\nOLDPWD: %s\n", ft_getenv("PWD"), ft_getenv("OLDPWD"));
// 	ft_pwd();
// 	ft_free_str_arr(c->cmd);
// 	ft_free_str_arr(s->env);
// 	free(s);
// 	free(c);
// }
