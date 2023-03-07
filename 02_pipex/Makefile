# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 20:41:46 by tfregni           #+#    #+#              #
#    Updated: 2023/02/20 15:56:30 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= pipex.c environment.c parse_args.c pipe_fork.c error_handling.c heredoc.c

OBJS	= ${SRCS:.c=.o}

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g

NAME	= pipex

LIB		= libft

RE_LIBFT	= "$(wildcard ./libft/libft.a)"

RM		= rm -f

all		:
	make ${NAME}

# ifneq wasn't working because of missing quotes
# ifneq ("${RE_LIBFT}" yes
# ifneq (${RE_LIBFT} no
# also, make -C ${LIB} calls the all rule that cleans
libft:
ifneq ("$(wildcard ${RE_LIBFT})", "./libft/libft.a")
	make libft.a -C ${LIB}
endif

${NAME}: ${OBJS}
	make libft
	${CC} ${CFLAGS} ${OBJS} ./${LIB}/libft.a -o ${NAME}

bonus	: ${NAME}

clean	:
	make clean -C ${LIB}
ifneq ("$(wildcard ${OBJS})", "")
	${RM} ${OBJS}
endif

fclean	: clean
	make fclean -C libft
ifneq ("$(wildcard ${NAME})", "")
	${RM} ${NAME}
endif

re		: fclean all

.PHONY	: all clean fclean bonus re libft
