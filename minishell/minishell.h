/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/04 18:25:41 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
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
# define TRAIL_CHAR " \n\t><|\"$/\'="
# define SPLIT_CHAR "><|"
# define SP_PARAM "@*#?-!\\/.+()[]{}"
# define BRACKETS "()"
# define N_BUILTINS 7
# define HEREDOC_NAME "_heredoc_temp"
# define QUOTES "\'\""
# define FLAG_CHAR 255
# define MAX_INT64 9223372036854775807

typedef enum s_bool
{
	false,
	true
}	t_bool;

enum e_token {
	S_QUOTE = '\'',
	D_QUOTE = '\"',
};

enum e_lexer_info
{
	LEX_CMD = 1,
	LEX_FILE,
	LEX_TERM
};

enum e_state
{
	IN_NORMAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

typedef enum e_redir
{
	OUT_WRITE = 1,
	OUT_APPEND,
	IN_READ,
	HEREDOC,
}	t_redir;

typedef struct s_shell	t_shell;
extern t_shell			*g_shell;

typedef struct s_builtins
{
	char		*name;
	void		(*func)(t_shell *s, t_command *c);
}				t_builtins;

struct s_shell
{
	char		**env;
	char		**params;
	char		*user;
	char		*prompt;
	t_bool		exit;
	t_bool		pipe;
	t_lexer		*lexer;
	t_command	*cmd;
	t_builtins	*builtins;
	int			status;
	t_bool		forked;
	pid_t		*pids;
};

/* PROMPT */
void			get_prompt(t_shell *s);
void			init_signal(void);

/* LEXER */
t_lexer			*lexer(char *fmt);
char			**lex_split_token(char *str);
char			*lex_expander(char *cmds);
int				lex_update_state(char *str, int *i, int *state);
int				lex_check_state(char *str, int i, int state);
t_lexer			*lex_list_from_table(char **matrix);
void			fill_lex_list(t_lexer **node, char *data, int info, int i);
void			lex_print_list(t_lexer *list);
void			free_lex(t_lexer **list);
void			for_each_lex_node(t_lexer **list, void (*f)(t_lexer **cmd));
void			lex_split_list(t_lexer **list);
char			**expander(char **arr);
void			add_flag_char(char **data);
char			*trim_param(char *cur, int i);
char			*retrieve_param(char *key);
t_bool			has_unclosed_quotes(char *str);

/* PARSER */
t_command		*parser(t_lexer *lex);
t_command		*par_list_new_node(t_lexer *start, int len);
void			par_list_add_back(t_command **list, t_command *new);
void			free_par(t_command **cmd);
void			par_trim_expand(t_command **cmd);
void			for_each_par_node(t_command **cmd, void (*f)(t_command **cmd));
void			par_fill_cmd(int *i, t_lexer *start, t_command **cmd_node);
t_redir			is_redir(char *str);
void			new_redir(int redir, t_lexer **lexer_node, \
				t_command **cmd_node);
void			setup_pipe(t_command *cmd, int n_cmds);
char			*trim_quotes(char *data);
void			free_lex_list(t_lexer **lex);
void			print_cmd_node(t_command **cmd);
void			trim_cmd(t_command **cmd);
void			trim_lex(t_lexer **token);
int				get_node_len(t_lexer **lex);
t_bool			is_pipe(char *str);
void			handle_heredoc(t_lexer *lex, int *open_flag);

/* EXECUTOR 	*/
void			execute(t_shell *s, t_command *parsed_cmd);
void			create_redir(t_command *cmd);
void			close_fd(t_command *cmd);
void			free_command(t_command *cmd);
int				find_builtin(t_shell *s, char *cmd);
void			add_param(t_shell *s, t_command *c);
void			parent_routine(t_command **command);
void			child_routine(t_shell *s, t_command *command, t_command *first);
char			*find_cmd(char *cmd);

/* EXEC SCRIPT */
void			exec_script(t_shell *s, int fd);

/* FREE */
void			free_shell(t_shell *shell);
void			free_builtins(t_builtins *b);
void			free_lex(t_lexer **list);
void			free_prompt(char *input, t_lexer **lex_list, \
				t_command **par_list);

/* BUILTINS 	*/
void			init_builtins(t_shell *s);
void			ft_cd(t_shell *s, t_command *c);
void			ft_pwd(t_shell *s, t_command *c);
void			ft_env(t_shell *s, t_command *c);
void			ft_unset(t_shell *s, t_command *c);
void			ft_export(t_shell *s, t_command *c);
void			ft_echo(t_shell *s, t_command *c);
void			ft_exit(t_shell *s, t_command *c);

/* BUILTINS 	UTILITIES */
char			**env_dup(char **env);
char			**env_append(char **env, char *var);
int				search_array(char **env, char *var);
int				arg_index(char **env, char *var);
char			*ft_getenv(char *key);
void			ft_export_append(char ***env, char *var);
void			ft_export_replace(char **env, char *var, int index);
t_bool			is_param(char *input);
t_bool			is_param_name(char *input);

/* ERROR HANDLING*/
int				throw_err(char *str, char *arg);
void			ft_error(char *general, char *err, char *arg, \
				uint8_t error_code);
void			add_status(int status);

#endif
