/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:28:27 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/24 17:14:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_pipe_status
{
	PIPE_READ,
	PIPE_WRITE,
	PIPE_NO,
}			t_pipe_status;

typedef struct s_command
{
	char				**cmd;
	int					infile;
	int					outfile;
	struct s_command	*next;
	struct s_command	*prev;
}				t_command;
#endif
