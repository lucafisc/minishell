F_SERVER = ./src/server.c ./src/utils.c
F_CLIENT = ./src/client.c ./src/utils.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client
PRINTF = ft_printf/ft_printf.a
LIBFT = libft/libft.a
INCLUDES = -I ft_printf/includes -I libft/includes
MAKE = make

all: $(SERVER) $(CLIENT)

$(SERVER): $(F_SERVER) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(F_SERVER) $(PRINTF) $(LIBFT) $(INCLUDES) -o $(SERVER)

$(CLIENT): $(F_CLIENT) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(F_CLIENT) $(PRINTF) $(LIBFT) $(INCLUDES) -o $(CLIENT)

$(PRINTF):
	$(MAKE) -C ft_printf

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) -C ft_printf clean
	$(MAKE) -C libft clean

fclean: clean
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C libft fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean
	$(MAKE) all