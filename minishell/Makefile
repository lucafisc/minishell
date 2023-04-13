SRC = main.c free.c signal.c search_bin.c \
		lexer.c lex_split_token.c lex_state.c lex_expander.c lex_list.c lex_utils.c lex_split_list.c \
		parser.c par_utils.c par_trim_expand.c par_list.c par_redir.c\
		 executor.c builtins.c $(addprefix builtins/,cd.c echo.c export.c pwd_env.c unset.c builtins_util.c)
OBJ = $(addprefix obj/, $(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
CLIENT = client
LIBFT = ./libft/libft.a
INCLUDES = -I libft
MAKE = make

all: $(NAME)

$(NAME): make_obj_dir $(OBJ)
	make $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

make_obj_dir:
	mkdir -p obj
	mkdir -p obj/builtins

obj/%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
ifneq ("$(wildcard $(OBJ))", "")
ifneq ("$(wildcard $(OBJ))", "")
	rm -f $(OBJ)
	rm -rf obj
endif
	@$(MAKE) -C libft clean
endif
	@$(MAKE) -C libft clean

fclean: clean
ifneq ("$(wildcard $(NAME))", "")
ifneq ("$(wildcard $(NAME))", "")
	rm -f $(NAME)
endif
	@$(MAKE) -C libft fclean
endif
	@$(MAKE) -C libft fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean