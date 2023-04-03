SRC = main.c lexer.c signal.c cmdtrim.c search_bin.c
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
	rm -f $(OBJ)
	rm -rf obj
	$(MAKE) -C libft clean

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
