/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:04:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/23 19:50:07 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* finds the full path of executable bin (if any) */
/* cmd needs to be freeable */
char	*find_cmd(t_shell *s, char *cmd)
{
	int		i;
	char	*tmp_prog;

	i = 0;
	while (s->path[i])
	{
		tmp_prog = ft_strnjoin(3, s->path[i], "/", cmd);
		if (access(tmp_prog, X_OK) != -1)
		{
			free(cmd);
			cmd = ft_strdup(tmp_prog);
			free(tmp_prog);
			g_shell->status = 0;
			return (cmd);
		}
		else if (access(tmp_prog, F_OK) == -1)
			g_shell->status = 127;
		else if (access(tmp_prog, X_OK) == -1)
			g_shell->status = 126;
		else
			g_shell->status = 1;
		free(tmp_prog);
		i++;
	}
	return (cmd);
}
