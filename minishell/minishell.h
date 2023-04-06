/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/06 12:17:21 by tfregni          ###   ########.fr       */
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
# include "colors.h"
# define TRAIL_CHAR " \n\t><|\"$"
# define SPLIT_CHAR "|<>"
# define N_BUILTINS 5

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

typedef struct s_builtins
{
	char	*name;
	void	(*func)(char *arg, char ***env);
}				t_builtins;

typedef struct s_shell
{
	char		**env;
	char		**path;
	char		*user;
	char		*prompt;
	t_lexer		*lexer;
	t_command	*cmd;
	t_builtins	*builtins;
}				t_shell;

t_lexer	*lexer(t_shell *s, char *fmt);
void	init_signal(void);
char	**ft_cmd_trim(char *str);
void	print_list(t_lexer **list);
void	split_list(t_lexer **list);
int		count_words(char const *s, char c);
void	find_cmd(t_shell *s, char *cmd);
char	**ft_split_keep(char const *s, char c);
t_lexer	*new_lexer_list_from_matrix(char **matrix);
void	free_lexer_list(t_lexer **list);
void	fill_lexer_list(t_lexer **node, char *data, int info, int i);

void	execute(t_shell *s, t_lexer *lex);
/* BUILTINS */
void	ft_cd(char *path, char ***env);
/* LIST UTILITIES */
t_lexer	*ft_dbllstnew(char *data, int info, int index);
void	ft_dbllst_addback(t_lexer **list, t_lexer *new);
/* ERROR HANDLING*/
int		throw_err(char *str, char *arg);

#endif
