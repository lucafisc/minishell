/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:04:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/04 18:25:01 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_valid_cmd(char **cmd, char **tmp_prog, char ***path)
{
	free(*cmd);
	*cmd = ft_strdup(*tmp_prog);
	free(*tmp_prog);
	g_shell->status = 0;
	ft_free_str_arr(*path);
}

/* finds the full path of executable bin (if any) */
/* cmd needs to be freeable */
char	*find_cmd(char *cmd)
{
	int		i;
	char	*tmp_prog;
	char	**path;

	path = ft_split(ft_getenv("PATH"), ':');
	i = 0;
	while (path && path[i])
	{
		tmp_prog = ft_strnjoin(3, path[i], "/", cmd);
		if (access(tmp_prog, X_OK) != -1)
		{
			handle_valid_cmd(&cmd, &tmp_prog, &path);
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
	ft_free_str_arr(path);
	return (cmd);
}
