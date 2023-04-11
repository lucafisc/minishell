/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/11 16:23:57 by tfregni          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "colors.h"
# define TRAIL_CHAR " \n\t><|\"$"
# define SPLIT_CHAR "|<>"
# define N_BUILTINS 6

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

typedef struct s_shell	t_shell;

typedef struct s_builtins
{
	char	*name;
	void	(*func)(t_shell *s, t_command *c);
}				t_builtins;

struct s_shell
{
	char		**env;
	char		**path;
	char		*user;
	char		*prompt;
	t_lexer		*lexer;
	t_command	*cmd;
	t_builtins	*builtins;
};

t_lexer	*lexer(t_shell *s, char *fmt);
void	init_signal(void);
char	**ft_cmd_trim(char *str);
void	print_list(t_lexer **list);
void	split_list(t_lexer **list);
int		count_words(char const *s, char c);
void	find_cmd(t_shell *s, char *cmd);
char	**ft_split_keep(char const *s, char c);
t_lexer	*new_lexer_list_from_matrix(char **matrix);
void	fill_lexer_list(t_lexer **node, char *data, int info, int i);
void	execute(t_shell *s, t_lexer *lex);

/* FREE */
void	free_builtins(t_builtins *b);
void	free_lexer_list(t_lexer **list);

/* BUILTINS */
void	init_builtins(t_shell *s);
void	ft_cd(t_shell *s, t_command *c);
void	ft_pwd(t_shell *s, t_command *c);
void	ft_env(t_shell *s, t_command *c);
void	ft_unset(t_shell *s, t_command *c);
void	ft_export(t_shell *s, t_command *c);
void	ft_echo(t_shell *s, t_command *c);

/* BUILTINS UTILITIES */
char	**env_dup(char **env);
char	**env_append(char **env, char *var);
int		search_array(char **env, char *var);
int		arg_index(char **env, char *var);
char	*ft_getenv(char **env, char *key);

/* LIST UTILITIES */
t_lexer	*ft_dbllstnew(char *data, int info, int index);
void	ft_dbllst_addback(t_lexer **list, t_lexer *new);

/* ERROR HANDLING*/
int		throw_err(char *str, char *arg);

#endif
