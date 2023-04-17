/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:04:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/17 11:15:00 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* finds the full path of executable bin (if any) */
/* cmd needs to be freeable */
char	*find_cmd(t_shell *s, char *cmd)
{
	int		i;
	char	*tmp_prog;

	// printf("Find command %s %p\n", cmd, cmd);
	i = 0;
	while (s->path[i])
	{
		tmp_prog = ft_strnjoin(3, s->path[i], "/", cmd);
		// printf("Trying command %s... ", tmp_prog);
		if (access(tmp_prog, X_OK) != -1)
		{
			free(cmd);
			cmd = ft_strdup(tmp_prog);
			free(tmp_prog);
			// printf("success: passing %s %p\n", cmd, cmd);
			return (cmd);
		}
		// printf("failed\n");
		free(tmp_prog);
		i++;
	}
	return (cmd);
}
