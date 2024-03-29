/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:09:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/27 14:57:19 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt(char *input, t_lexer **lex_list, t_command **par_list)
{
	(void)par_list;
	free(input);
	for_each_lex_node(lex_list, free_lex);
	for_each_par_node(par_list, free_par);
}
