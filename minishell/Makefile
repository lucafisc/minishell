# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 13:03:17 by tfregni           #+#    #+#              #
#    Updated: 2023/04/29 21:50:51 by tfregni          ###   ########.fr        #
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
OS := $(shell uname)
ARCH := $(shell uname -m)
LIBFT = ./libft/libft.a
LIBS = -lreadline
MAKE = make

# Check the includes and libs on Linux or ARM64
ifeq ($(OS), Darwin)
ifeq ($(ARCH), x86_64)
INCLUDES += -I /usr/local/Cellar/readline/8.2.1/include
LIBS += -L /usr/local/Cellar/readline/8.2.1/lib
endif
endif

all: $(NAME)
	@./minishell

val: $(NAME)
	@valgrind --leak-check=full --track-fds=yes ./minishell

$(NAME): $(OBJ)
	@clear
	@make $(LIBFT)
	@printf "Building minishell... "
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME) $(LIBS)
	@echo "Done!"
	@echo
	@echo "  __  __ _       _ _    _      _ _ "
	@echo " |  \/  (_)     (_) |  | |    | | | "
	@echo " | \  / |_ _ __  _| |__| | ___| | | "
	@echo " | |\/| | | '_ \| |  __  |/ _ \ | | "
	@echo " | |  | | | | | | | |  | |  __/ | | "
	@echo " |_|  |_|_|_| |_|_|_|  |_|\___|_|_| "
	@echo
	@echo
	@echo "	by lde-ross & tfregni @42Berlin"
	@echo

$(LIBFT):
	@$(MAKE) -C libft

# https://www.gnu.org/software/make/manual/html_node/Prerequisite-Types.html
# The | char in makefile makes what follows a prerequisite but it won't recompile
# if its timestamp changed
$(OBJ): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/builtins

$(OBJDIR)/%.o: %.c
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@printf "Cleaning up... "
ifneq ("$(wildcard $(OBJ))", "")
	@rm -f $(OBJ)
	@rm -rf obj
endif
	@$(MAKE) -C libft clean
	@echo "Done"
	@echo

fclean: clean
ifneq ("$(wildcard $(NAME))", "")
	@rm -f $(NAME)
endif
	@$(MAKE) -C libft fclean

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean
