/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/28 14:37:55 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include "./libft/libft.h"
# include "lexer.h"

enum Token {
	S_QUOTE = '\'',
	D_QUOTE = '\"',
};

enum {
	IN_NORMAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

typedef struct s_shell
{
	char	**env;
	char	**path;
}				t_shell;

t_lexer	**lexer(char *fmt);
#endif
