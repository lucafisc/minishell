/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsubsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 21:04:58 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/31 21:28:02 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	count_cmds(char **cmds)
// {
// 	int	count;
// 	int	i;
// 	int	j;

// 	while (cmds[i])
// 	{
// 		j = 0;
// 		if (cmds[i][j] == '\"' || cmds[i][j] == '\'')
// 		{
// 			count++;
// 		}
// 		else
// 		{
// 			while (cmds[i][j])
// 			{
// 				if (cmds[i][j] == '|' || cmds[i][j] == '<' || cmds[i][j] == '>')
// 				{
// 					count++;
// 					break;
// 				}
// 				j++;
// 			}
// 		}
// 			i++;
// 	}
	
// }

char	**cmdsubsplit(char **cmds)
{
	int	n_cmds;

	n_cmds = count_cmds(cmds);
}