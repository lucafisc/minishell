# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 13:34:50 by tfregni           #+#    #+#              #
#    Updated: 2023/04/11 16:13:54 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c lexer.c signal.c cmdtrim.c search_bin.c lexer_list.c ft_split_keep.c \
		lexer_list_utils.c executor.c $(addprefix builtins/,cd.c echo.c export.c pwd_env.c unset.c builtins_util.c)
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
