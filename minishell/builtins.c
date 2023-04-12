/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/11 16:24:04 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "./builtins/cd.c"

void	free_builtins(t_builtins *b)
{
	free(b);
}

void	init_builtins(t_shell *s)
{
	t_builtins	*b;

	b = malloc(sizeof(*b) * (N_BUILTINS + 1));
	b[N_BUILTINS].name = NULL;
	b[0] = (t_builtins){"cd", ft_cd};
	b[1] = (t_builtins){"echo", ft_echo};
	b[2] = (t_builtins){"export", ft_export};
	b[3] = (t_builtins){"pwd", ft_pwd};
	b[4] = (t_builtins){"unset", ft_unset};
	b[5] = (t_builtins){"env", ft_env};
	s->builtins = b;
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
// 	init_builtins(s);
// 	c->cmd[ac] = NULL;
// 	s->env = env_dup(env);
// 	s->builtins[0].func (s, c);
// 	printf("cwd: %s\n", getcwd(NULL, 0));
// 	ft_free_str_arr(c->cmd);
// 	ft_free_str_arr(s->env);
// 	free_builtins(s->builtins);
// 	free(c);
// 	free(s);
// }
