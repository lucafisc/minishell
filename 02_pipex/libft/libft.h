/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:02:27 by tfregni           #+#    #+#             */
/*   Updated: 2023/02/01 19:53:29 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "./get_next_line/get_next_line.h"

// Part1
int				ft_isalpha(int a);
int				ft_isdigit(int n);
int				ft_isalnum(int a);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *str);
void			*ft_memset(void *ptr, int ch, size_t len);
void			ft_bzero(void *ptr, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *str, char c);
char			*ft_strrchr(char *str, char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(char *str, char *to_find, int len);
int				ft_atoi(const char *nbr);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *src);

// Part2
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

// Bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
							void (*del)(void *));

// Extra
int				ft_printf(const char *str, ...);
char			*get_next_line(int fd);
void			ft_mergesort(int *arr, int start, int end);
void			ft_mergesort_des(int *arr, int start, int end);
int				ft_abs(int n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strnjoin(ssize_t n, ...);
void			ft_free_str_arr(char **arr);
int				ft_arrlen(char **argv);
void			ft_print_strarr(char **arr);
/*
 * Dynamic array that can automatically expand when necessary
 *
 * Methods:
 *   ft_dyn_arr_new
 *   ft_dyn_arr_pushback
 *   ft_dyn_arr_clear
 *   ft_dyn_arr_erase
 */
typedef struct s_dyn_arr
{
	char		**ptr;
	size_t		len;
	size_t		cap;
}				t_dyn_arr;

t_dyn_arr		*ft_dyn_arr_new(size_t cap);
void			ft_dyn_arr_pushback(t_dyn_arr *dyn_arr, char *item);
void			ft_dyn_arr_clear(t_dyn_arr *dyn_arr);
void			ft_dyn_arr_erase(t_dyn_arr *dyn_arr, char *item);

#endif
