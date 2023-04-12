/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:02:56 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/12 15:04:54 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Updates the status for the character the given matrix
is pointing to, moves on the pointer and returns a code */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	lex_update_state(char *str, int *i, int *state)
{
	int	res;

	if (!str || !state)
		return (-1);
	res = 1;
	if (*state == IN_D_QUOTE && str[*i] == '"' && str[*i - 1] != '\\')
		*state = IN_NORMAL;
	else if (*state == IN_S_QUOTE && str[*i] == '\'' && str[*i - 1] != '\\')
		*state = IN_NORMAL;
	else if (*state == IN_NORMAL && (str[*i] == '"' || str[*i] == '\'') && (*i == 0 || str[*i - 1] != '\\'))
	{
		res = 2;
		if (str[*i] == '"')
			*state = IN_D_QUOTE;
		else if (str[*i] == '\'')
			*state = IN_S_QUOTE;
	}
	else
		res = 0;
	*i += 1;
	return (res);
}

/* Checks if the given character entails a state change */
/* 0 - no change */
/* 1 - close quotes */
/* 2 - open quotes */
int	lex_check_state(char *str, int i, int state)
{
	int	res;

	if (!str || !str[i])
		return (0);
	if ((state == IN_D_QUOTE && str[i] == '"' && str[i - 1] != '\\') || \
	(state == IN_S_QUOTE && str[i] == '\'' && str[i - 1] != '\\'))
		res = 1;
	else if (state == IN_NORMAL && (str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		res = 2;
	else
		res = 0;
	return (res);
}
