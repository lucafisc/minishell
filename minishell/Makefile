# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 13:03:17 by tfregni           #+#    #+#              #
#    Updated: 2023/04/27 17:09:18 by lde-ross         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c prompt.c free.c signal.c search_bin.c \
		lexer.c lex_split_token.c lex_state.c lex_expander.c lex_list.c lex_utils.c lex_split_list.c \
		parser.c par_utils.c par_trim_expand.c par_list.c par_redir.c par_redir_utils.c par_node.c\
		 executor.c exec_utils.c builtins.c $(addprefix builtins/,cd.c echo.c export.c pwd_env.c unset.c exit.c builtins_util.c)\
		 exec_script.c error_handling.c
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
CLIENT = client
LIBFT = ./libft/libft.a
# Check the includes and libs on Linux or ARM64
INCLUDES = -I /usr/local/Cellar/readline/8.2.1/include
LIBS = -L /usr/local/Cellar/readline/8.2.1/lib -lreadline
MAKE = make

all: $(NAME)

$(NAME): $(OBJ)
	make $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME) $(LIBS)

$(LIBFT):
	@$(MAKE) -C libft

# https://www.gnu.org/software/make/manual/html_node/Prerequisite-Types.html
# The | char in makefile makes what follows a prerequisite but it won't recompile
# if its timestamp changed
$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/builtins

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
ifneq ("$(wildcard $(OBJ))", "")
	rm -f $(OBJ)
	rm -rf obj
endif
	@$(MAKE) -C libft clean

fclean: clean
ifneq ("$(wildcard $(NAME))", "")
	rm -f $(NAME)
endif
	@$(MAKE) -C libft fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean
