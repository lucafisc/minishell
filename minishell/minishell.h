/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/03/30 10:48:28 by tfregni          ###   ########.fr       */
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
# include <string.h>
# include <errno.h>
# include "./libft/libft.h"
# include "lexer.h"
# include "parser.h"

typedef enum s_bool
{
	false,
	true
}	t_bool;

enum e_token {
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
	char		**env;
	char		**path;
	t_lexer		*lexer;
	t_command	*cmd;
}				t_shell;

t_lexer	*lexer(char *fmt);
#endif
