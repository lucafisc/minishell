/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:19:22 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/03 18:47:37 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	b[6] = (t_builtins){"exit", ft_exit};
	s->builtins = b;
}
