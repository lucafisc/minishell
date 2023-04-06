/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/06 09:32:17 by lde-ross         ###   ########.fr       */
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
# define TRAIL_CHAR " \n\t><|\"$"
# define SPLIT_CHAR "|<>"

typedef enum s_bool
{
	false,
	true
}	t_bool;

enum e_token {
	S_QUOTE = '\'',
	D_QUOTE = '\"',
};

enum e_state {
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
void	init_signal(void);
char	**ft_cmd_trim(char *str);
void	print_list(t_lexer **list);
void	split_list(t_lexer **list);
int		count_words(char const *s, char c);
char	**ft_split_keep(char const *s, char c);
t_lexer	*ft_dbllstnew(char *data, int info, int index);
void	ft_dbllst_addback(t_lexer **list, t_lexer *new);
t_lexer	*new_lexer_list_from_matrix(char **matrix);
void	free_lexer_list(t_lexer **list);
void	fill_lexer_list(t_lexer **node, char *data, int info, int i);


#endif
