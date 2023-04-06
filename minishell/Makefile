# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 13:34:50 by tfregni           #+#    #+#              #
#    Updated: 2023/04/06 10:55:52 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c lexer.c signal.c cmdtrim.c search_bin.c lexer_list.c ft_split_keep.c \
		executor.c
OBJ = $(addprefix obj/, $(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
CLIENT = client
LIBFT = ./libft/libft.a
INCLUDES = -I libft
MAKE = make

all: $(NAME)

$(NAME): $(OBJ)
	make $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

obj/%.o: %.c
	mkdir -p obj
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
