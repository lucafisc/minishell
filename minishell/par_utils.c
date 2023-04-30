/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:56:16 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/30 14:29:47 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	for_each_par_node(t_command **cmd, void (*f)(t_command **cmd))
{
	t_command	*cur;
	t_command	*temp;

	cur = *cmd;
	while (cur)
	{
		temp = cur->next;
		f(&cur);
		cur = temp;
	}
}

void	free_par(t_command **cmd)
{
	int			i;
	t_command	*c;

	c = *cmd;
	i = 0;
	while (c->cmd && c->cmd[i])
	{
		free(c->cmd[i]);
		i++;
	}
	if (c->infile != -1)
		close(c->infile);
	if (c->outfile != -1)
		close(c->outfile);
	free(c->cmd);
	free(c);
}

void	add_flag_char(char **data)
{
	char	*flagged;
	int		len;
	int		i;

	len = ft_strlen(*data);
	flagged = ft_calloc(sizeof(*flagged), len + 2);
	if (!flagged)
		return ;
	ft_strlcpy(flagged, *data, len + 1);
	i = 0;
	while (flagged[i])
		i++;
	flagged[i] = (char) FLAG_CHAR;
	free(*data);
	*data = flagged;
}

t_bool	is_in_quote(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0])
		return (true);
	return (false);
}