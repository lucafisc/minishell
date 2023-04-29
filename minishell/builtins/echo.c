/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:46:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/30 00:21:05 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		// var = clean_variable(args[i]);
		var = ft_strdup(args[i]);
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
