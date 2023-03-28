/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:12:19 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/28 14:47:26 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	**lexer(char *fmt)
{
	t_lexer	**tokens;
	char	**raw_tokens;
	int		i;

	raw_tokens = ft_split(fmt, ' ');
	i = ft_arrlen(raw_tokens);
	tokens = malloc(sizeof(*tokens) * (i + 1));
	tokens[i] = malloc(sizeof(*tokens[i]));
	tokens[i]->data = NULL;
	write(2, "here\n", 5);
	while (--i >= 0)
	{
		tokens[i] = malloc(sizeof(*tokens[i]));
		tokens[i]->data = ft_strdup(raw_tokens[i]);
		tokens[i]->info = i;
	}
	while (tokens[++i]->data)
	{
		printf("%d - %s\n", tokens[i]->info, tokens[i]->data);
	}
	return (tokens);
}