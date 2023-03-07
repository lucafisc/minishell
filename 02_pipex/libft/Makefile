SRCS		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
				ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
				ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_print_strarr.c

SRCS_BNS	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRCS_EXTRA	=	$(addprefix ./ft_printf/, ft_printf.c parse_argument.c parse_flag.c parse_num.c parse_ptr.c parse_text.c padding.c print_num.c print_ptr.c print_text.c)\
				$(addprefix ./get_next_line/, get_next_line.c get_next_line_utils.c)\
				ft_mergesort.c ft_mergesort_des.c ft_abs.c ft_strcmp.c \
				ft_dyn_arr_new.c ft_dyn_arr_pushback.c ft_dyn_arr_clear.c ft_dyn_arr_erase.c \
				ft_strnjoin.c ft_free_str_arr.c ft_arrlen.c

OBJS	= ${SRCS:.c=.o}

OBJS_BNS	= ${SRCS_BNS:.c=.o}

OBJS_EXTRA	= ${SRCS_EXTRA:.c=.o}

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

AR		= ar rc

LIB		= ranlib

NAME	= libft.a

RM		= rm -f

all		: ${NAME}
	make clean

${NAME}: ${OBJS} ${OBJS_BNS} ${OBJS_EXTRA}
	${AR} ${NAME} ${OBJS} ${OBJS_BNS} ${OBJS_EXTRA}
	${LIB} ${NAME}

bonus	: ${NAME} ${OBJS_BNS}
	${AR} ${NAME} ${OBJS_BNS}
	${LIB} ${NAME}

extra	: bonus ${OBJS_EXTRA}
	${AR} ${NAME} ${OBJS_EXTRA}
	${LIB} ${NAME}

clean	:
ifneq ("$(wildcard  ${OBJS} ${OBJS_BNS} ${OBJS_EXTRA})", "")
	${RM} ${OBJS} ${OBJS_BNS} ${OBJS_EXTRA}
endif

fclean	: clean
ifneq ("$(wildcard ${NAME})", "")
	${RM} ${NAME}
endif

re		: fclean all

.PHONY	: all clean fclean re bonus extra
