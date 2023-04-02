/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:33:56 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/02 09:29:48 by tfregni          ###   ########.fr       */
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
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	if (arg && arg[0])
	{
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
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

void	ft_cd(char *path, char ***env)
{
	char	old_dir[PATH_MAX];
	char	*dir;

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
		throw_err("cd", dir);
	/* Update environment: OLDPWD=old_dir, PWD=dir */
	update_pwd(env, old_dir, dir);
	// getcwd(old_dir, sizeof(old_dir));
	free(dir);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	env = env_dup(env);
	ft_cd("/bin", &env);
	printf("PWD: %s\nOLDPWD: %s\n", ft_getenv(env, "PWD"), ft_getenv(env, "OLDPWD"));
	ft_pwd();
	ft_free_str_arr(env);
}

