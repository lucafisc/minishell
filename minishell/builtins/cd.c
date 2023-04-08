/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:33:56 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/08 18:34:40 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "export.c"
#include "pwd_env.c"

/* more elaborate version of throw error */
int	throw_err(char *str, char *arg)
{
	if (str && str[0])
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	if (arg && arg[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	write(2, "\n", 1);
	return (1);
}

void	update_pwd(char ***env, char *old_pwd, char *pwd)
{
	char	*update_env;

	update_env = ft_strjoin("OLDPWD=", old_pwd);
	// printf("%s\n", update_env);
	ft_export(env, update_env);
	free(update_env);
	update_env = ft_strjoin("PWD=", pwd);
	// printf("%s\n", update_env);
	ft_export(env, update_env);
	free(update_env);
}

// void	ft_cd(char *path, char ***env)
// {
// 	char	old_dir[PATH_MAX];
// 	char	*dir;

// 	/* PATH_MAX is the max depth of the path */
// 	// Save the current dir to set is as OLDPWD when done
// 	if (!getcwd(old_dir, sizeof(old_dir)))
// 		throw_err("cd", NULL);
// 	// case of ~ alone, empty parameter or no parameter -> HOME
// 	if (!ft_strncmp(path, "~", 2) || !path || !path[0])
// 		dir = ft_strdup(getenv("HOME"));
// 	// case of - -> OLDPWD
// 	else if (!ft_strncmp(path, "-", 2))
// 		dir = ft_strdup(getenv("OLDPWD"));
// 	// case of ~/something -> expand ~ to HOME
// 	else if (path[0] == '~')
// 		dir = ft_strnjoin(2, getenv("HOME"), (path + 1));
// 	// case normal
// 	else
// 		dir = ft_strdup(path);
// 	if (chdir(dir) == -1)
// 		throw_err("cd", dir);
// 	/* Update environment: OLDPWD=old_dir, PWD=dir */
// 	update_pwd(env, old_dir, dir);
// 	// getcwd(old_dir, sizeof(old_dir));
// 	free(dir);
// }

void	ft_cd(t_shell *s, t_command *c)
{
	char	old_dir[PATH_MAX];
	char	*dir;
	char	*path;

	path = c->cmd[1];
	/* PATH_MAX is the max depth of the path */
	// Save the current dir to set is as OLDPWD when done
	if (!getcwd(old_dir, sizeof(old_dir)))
		throw_err("cd", NULL);
	// case of ~ alone, empty parameter or no parameter -> HOME
	if (!ft_strncmp(path, "~", 2) || !path || !path[0])
		dir = ft_strdup(getenv("HOME"));
	// case of - -> OLDPWD
	else if (!ft_strncmp(path, "-", 2))
		dir = ft_strdup(getenv("OLDPWD"));
	// case of ~/something -> expand ~ to HOME
	else if (path[0] == '~')
		dir = ft_strnjoin(2, getenv("HOME"), (path + 1));
	// case normal
	else
		dir = ft_strdup(path);
	if (chdir(dir) == -1)
	{
		throw_err("cd", dir);
		return ;
	}
	/* Update environment: OLDPWD=old_dir, PWD=dir */
	update_pwd(&(s->env), old_dir, dir);
	// getcwd(old_dir, sizeof(old_dir));
	free(dir);
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
	ft_strlcpy(c->cmd[0], "cd", 3);
	if (ac > 1)
		ft_strlcpy(c->cmd[1], av[1], ft_strlen(av[1]) + 1);
	else
		ft_strlcpy(c->cmd[1], "/bin", 5);
	c->cmd[2] = NULL;
	s->env = env_dup(env);
	ft_cd(s, c);
	printf("PWD: %s\nOLDPWD: %s\n", ft_getenv(s->env, "PWD"), ft_getenv(s->env, "OLDPWD"));
	ft_pwd();
	ft_free_str_arr(c->cmd);
	ft_free_str_arr(s->env);
	free(s);
	free(c);
}
