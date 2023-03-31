SRC = main.c lexer.c signal.c
OBJ = $(addprefix obj/, $(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
CLIENT = client
LIBFT = ./libft/libft.a
INCLUDES = -I libft
MAKE = make

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

obj/%.o: %.c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)
	rmdir obj
	$(MAKE) -C libft clean

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
