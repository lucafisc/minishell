/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:46:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/23 14:49:41 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_echo works assuming a null terminated 2D array of args is given as input.
// if the option -n is enabled, the string "-n" should be at index 0 of this array
// it assumes the parser will interpret the arguments before

//in this case args[1] should equal "hello         hi":
// echo "hello         hi"
// hello         hi

//in this case args[1] should equal "hello" and args[2] should equal "hi":
// echo hello         hi
// hello hi

#include "../minishell.h"

// void	ft_echo(char **args)
// {
// 	t_bool	n;
// 	int		i;

// 	if (!args)
// 		return ;
// 	n = true;
// 	i = 0;
// 	if (args[i] && !ft_strcmp(args[i], "-n"))
// 	{
// 		i++;
// 		n = false;
// 	}
// 	while (args[i])
// 	{
// 		ft_putstr_fd(args[i], 1);
// 		// printf("%s", args[i]);
// 		if (args[i + 1])
// 			// printf(" ");
// 			ft_putchar(" ", 1);
// 		i++;
// 	}
// 	if (n)
// 		ft_putchar("\n", 1);
// 		// printf("\n");
// }

/* The variable expansion works already even if it's not
implemented in the function: it means it's running on every
string passed to the shell before calling any cmd */
void	ft_echo(t_shell *s, t_command *c)
{
	char	**args;
	t_bool	n;
	int		i;

	(void) s;
	if (!c || !c->cmd)
		return ;
	args = c->cmd;
	n = true;
	i = 1;
	if (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		i++;
		n = false;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], c->outfile);
		if (args[i + 1])
			ft_putchar_fd(' ', c->outfile);
		i++;
	}
	if (n)
		ft_putchar_fd('\n', c->outfile);
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
// 	ft_echo(s, c);
// 	ft_free_str_arr(c->cmd);
// 	ft_free_str_arr(s->env);
// 	free(s);
// 	free(c);
// }
