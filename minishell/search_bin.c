/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:04:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/14 18:03:58 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* finds the full path of executable bin (if any) */
/* cmd needs to be freeable */
void	find_cmd(t_shell *s, char *cmd)
{
	int		i;
	char	*tmp_prog;

	i = 0;
	while (s->path[i])
	{
		tmp_prog = ft_strnjoin(3, s->path[i], "/", cmd);
		if (access(tmp_prog, X_OK) != -1)
		{
			//free(cmd); this line was giving write errors...
			cmd = ft_strdup(tmp_prog);
			free(tmp_prog);
			break ;
		}
		free(tmp_prog);
		i++;
	}
}
