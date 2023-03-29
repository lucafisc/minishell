/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/29 15:57:53 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && n - 1 > 0)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

void	ft_export(char **env, char *var)
{
	int		len;
	char 	**new_env;

	len = 0;
	while (env[len])
	{
		len++;
	}

}

void ft_changeenv(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "arg", 3))
		{
			char new_arg[] = "arg=changed";
			*env = new_arg;
		}
		env++;
	}
}

void	ft_mispoint(char ***env)
{
	char	**new;

	new = malloc(sizeof(*new) * 3);
	new[0] = ft_strdup("hello");
	new[1] = ft_strdup("world");
	new[2] = NULL;
	*env = new;
}

int	main(int ac, char **av, char **environ)
{
	(void) ac;
	(void) av;
	// ft_pwd();
	ft_env(environ);
	// ft_changeenv(environ);
	// printf("------------------------\n");
	// ft_env(environ);
	ft_mispoint(&environ);
	ft_env(environ);
}
