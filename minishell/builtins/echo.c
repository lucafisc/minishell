/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:46:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/29 10:13:09 by tfregni          ###   ########.fr       */
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

char	*clean_variable(char *input)
{
	char	*var;
	char	**arr;

	arr = ft_split(input, ' ');
	var = ft_strnjoinchar(arr, ' ');
	ft_free_str_arr(arr);
	return (var);
}

int	is_flag_in_token(char *str)
{
	int	j;

	j = 1;
	if (str && ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[j] == 'n')
			j++;
		if (!str[j])
			return (true);
	}
	return (false);
}

t_bool	check_echo_flag(char **args, int *i)
{
	int			j;
	t_bool		flag;

	j = 1;
	flag = 0;
	if (is_flag_in_token(args[*i]))
	{
		flag = true;
		(*i)++;
		while (is_flag_in_token(args[(*i)]))
			(*i)++;
	}
	return (flag);
}

/* The variable expansion works already even if it's not
implemented in the function: it means it's running on every
string passed to the shell before calling any cmd */
void	ft_echo(t_shell *s, t_command *c)
{
	char	**args;
	t_bool	n;
	int		i;
	char	*var;

	(void) s;
	if (!c || !c->cmd)
		return ;
	trim_cmd(&c);
	args = c->cmd;
	i = 1;
	n = check_echo_flag(args, &i);
	while (args[i])
	{
		var = clean_variable(args[i]);
		ft_putstr_fd(var, c->outfile);
		if (var[0] && args[i + 1])
			ft_putchar_fd(' ', c->outfile);
		i++;
		free(var);
	}
	if (!n)
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
