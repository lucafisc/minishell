/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:32:00 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/29 12:58:50 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lex_list(t_lexer **lex)
{
	t_lexer	*tmp;

	while (*lex)
	{
		tmp = (*lex)->next;
		free((*lex)->data);
		free(*lex);
		*lex = tmp;
	}
}

void	print_cmd_node(t_command **cmd)
{
	t_command	*c;

	c = *cmd;
	ft_print_strarr(c->cmd);
}

void	trim_cmd(t_command **cmd)
{
	int			i;
	char		*temp;
	t_command	*command;

	i = 0;
	command = *cmd;
	while (command->cmd[i])
	{
		temp = trim_quotes(command->cmd[i]);
		free(command->cmd[i]);
		command->cmd[i] = temp;
		// printf("trim_cmd cmd[i] %p\n", command->cmd[i]);
		i++;
	}
}

int	get_node_len(t_lexer **lex)
{
	int		len;
	t_lexer	*current;

	len = 0;
	current = *lex;
	while (current && !is_pipe(current->data))
	{
		if (is_redir(current->data))
		{
			current = current->next;
			if (current)
				current->info = LEX_FILE;
		}
		else
			len++;
		if (current)
			current = current->next;
	}
	*lex = current;
	return (len);
}
