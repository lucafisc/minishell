/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:30:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/04/25 21:48:17 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ESCAPE "\\'\""

int	ft_count_tokens(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]))
			i++;
		else
		{
			count++;
			while (str[i] && !ft_is_space(str[i]))
				i++;
		}
	}
	return (count);
}

int	ft_add_cmd(char **arr, char *str, int *cmd)
{
	int	space;
	int	i;

	space = 0;
	i = 0;
	// printf("found word at %s\n", str);
	while (str[i] && !ft_is_space(str[i]))
		i++;
	if (ft_is_space(str[i]))
		space = 1;
	arr[(*cmd)++] = ft_substr(str, 0, i + space);
	// printf("added a word %d long: %s\n", i, arr[(*cmd) - 1]);
	return (i);
}

char	**ft_split_tokens(char *str)
{
	char	**arr;
	int		i;
	int		cmd;
	int		state;

	state = IN_NORMAL;
	arr = ft_calloc(ft_count_tokens(str) + 1, sizeof(*arr));
	if (!arr)
		return (NULL);
	cmd = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]))
			i++;
		else
		{
			str += i;
			i = ft_add_cmd(arr, str, &cmd);
			// printf("pointing at %c\n", str[i]);
		}
	}
	arr[cmd] = NULL;
	return (arr);
}

t_bool	is_next_new_tok(char *str, int i)
{
	if ((ft_is_space(str[i]) && !ft_is_space(str[i + 1]) && str[i + 1]) || (i == 0 && !ft_is_space(str[i])))
		return (true);
	return (false);
}



int	count_tokens(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		//printf("checking str[%d]:%c\n", i, str[i]);
		if (is_next_new_tok(str, i))
		{
			count++;
			//printf("count is now %d\n", count);
		}
		if (str[i] == '\"' || str[i] == '\'')
			i = ft_skip_char(str, str[i], i);
		i++;
	}
	return (count);
}

char	**lex_split_token(char *str)
{
	int		n_cmds;
	char	**arr;
	int		i;
	int		start;
	int		len = 0;
	int		prev;
	int		j;

	n_cmds = count_tokens(str);

	arr = malloc(sizeof(*arr) * (n_cmds + 1));
	if (!arr)
		return (NULL);
	arr[n_cmds] = NULL;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_next_new_tok(str, i))
		{
			printf("new tok: str[%d]:%c\n", i, str[i]);
			if (i != 0)
				i++;
			start = i;
			len = 0;
			while (str[i] && !ft_is_space(str[i]))
			{
				if (str[i] == '\"' || str[i] == '\'')
				{
					prev = i;
					i = ft_skip_char(str, str[i], i);
					i++;
					printf("str[%d] after skipped: %c\n", i, str[i]);
					len += i - prev;
				}
				else
				{
					i++;
					len++;
				}
			}
			arr[j] = ft_substr(str, start, len);
			printf("start: %d len %d\n", start, len);

			j++;
		}
		else
			i++;
	}
	printf("\n\n\n_________\n");
	ft_print_strarr(arr);
	exit(1);
}

// void	ft_update_state(char c, int *state, int *prev_state)
// {
// 	if (state == IN_NORMAL)
// 	{
// 		*prev_state = *state;
// 		if (c == S_QUOTE)
// 			*state = IN_S_QUOTE;
// 		else if (c == D_QUOTE)
// 			*state = IN_D_QUOTE;
// 	}
// 	else if (state == IN_S_QUOTE)
// 	{
// 		if (c == S_QUOTE) // close quotes
// 		{
// 			*state = *prev_state;
// 			*prev_state = IN_NORMAL;
// 		}
// 		else if (c == D_QUOTE) // open quotes
// 		{
// 			*prev_state =*state;
// 			*state = IN_D_QUOTE;
// 		}
// 	}
// 	else if (c == D_QUOTE)
// 	{
// 		if (c == D_QUOTE) // close quotes
// 		{
// 			*state = *prev_state;
// 			*prev_state = IN_NORMAL;
// 		}
// 		else if (c == S_QUOTE) // open quotes
// 		{
// 			*prev_state = *state;
// 			*state = IN_S_QUOTE;
// 		}
// 	}
// }

void	ft_update_state(char c, int *state, int *prev_state)
{
	if (*state == IN_NORMAL || \
	(*state == IN_S_QUOTE && c == D_QUOTE) || \
	(*state == IN_D_QUOTE && c == S_QUOTE))
	{
		*prev_state = *state;
		if (c == S_QUOTE)
			*state = IN_S_QUOTE;
		else
			*state = IN_D_QUOTE;
	}
	else if ((*state == IN_S_QUOTE && c == S_QUOTE) || \
	(*state == IN_D_QUOTE && c == D_QUOTE))
	{
		*state = *prev_state;
		*prev_state = IN_NORMAL;
	}
}

#define QUOTES "\'\""
int	is_new_word(char const *s, int i, int state, int prev_state)
{
	int	initial_state;

	initial_state = state;
	if ((i == 0 && !ft_is_space(s[i])) || (!ft_is_space(s[i]) && ft_is_space(s[i - 1])))
	{
		if (!ft_strchr(QUOTES, s[i]) && state == IN_NORMAL)
			return (1);
		if (ft_strchr(QUOTES, s[i]))
		{
			ft_update_state(s[i], &state, &prev_state);
			if (state != initial_state && initial_state == IN_NORMAL)
				return (1);
		}
	}
	return (0);
}

int	ft_count_tokens_by_char(char *str)
{
	int	state;
	int	prev_state;
	int	i;
	int	count;

	count = 0;
	state = IN_NORMAL;
	prev_state = state;
	i = 0;
	while (str[i])
	{
		if (is_new_word(str, i, state, prev_state))
		{
			count++;
			printf("tim: new word at %s\n", &str[i]);
		}
		if ((str[i] == S_QUOTE || str[i] == D_QUOTE) && (i > 0 && str[i - 1] != '\\'))
			ft_update_state(str[i], &state, &prev_state);
		i++;
	}
	return (count);
}

char	**ft_split_tokens_by_char(char *str)
{
	char	**arr;
	int		len;
	int		cmd;
	int		i;
	int		state;
	int		prev_state;

	len = ft_count_tokens_by_char(str);
	arr = ft_calloc(len + 1, sizeof(*arr));
	cmd = -1;
	state = IN_NORMAL;
	prev_state = state;
	i = 0;
	while (str[i])
	{
		if (is_new_word(str, i, state, prev_state))
		{
			cmd++;
			printf("cmd: %d at %s\n", cmd, &str[i]);
			if (cmd > 0)
			{
				arr[cmd - 1] = ft_substr(str, 0, i);
				printf("written arr[%d]: %s\n", cmd - 1, arr[cmd - 1]);
				str += i;
				i = 0;
			}
		}
		if ((str[i] == S_QUOTE || str[i] == D_QUOTE) && (i > 0 && str[i - 1] != '\\'))
			ft_update_state(str[i], &state, &prev_state);
		i++;
	}
	if (i > 0)
	{
		arr[cmd] = ft_substr(str, 0, i);
		printf("written arr[%d]: %s\n", cmd - 1, arr[cmd - 1]);
	}
	printf("len: %d cmd: %d\n", len, cmd);
	arr[cmd + 1] = NULL;
	return (arr);
}

// t_lexer	*ft_lexer(t_shell *s, char *input)
// {
// 	char	**table;

// 	table = ft_split_tokens;
// }

/* Given a string without spaces it cleans it from outer quotes
keeping inner quotes. It frees the given data.
TODO Flag if a quote is not closed in the data */
char	*trim_quotes(char *data)
{
	int		i;
	int		j;
	char	*trimmed;
	char	c;

	trimmed = ft_calloc(ft_strlen(data) + 1, sizeof(*trimmed));
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (data[i])
	{
		if (ft_strchr(QUOTES, data[i]))
		{
			c = data[i];
			i++;
			while (data[i] && data[i] != c)
				trimmed[j++] = data[i++];

		}
	}
	free(data);
	return (trimmed);
}

int	ft_count_words_keep(char *s)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_is_space(s[i]))
			return (printf("Found a space!\n"));
		if (ft_strchr(QUOTES, s[i]) && (i == 0 || !ft_strchr(QUOTES, s[i - 1])))
		{
			count++;
			c = s[i++];
			printf("enter quotes at %c count: %d\n", c, count);
			while (s[i] && s[i] != c)
				i++;
			printf("exit quotes at %s\n", &s[i]);
		}
		if (ft_strchr(SPLIT_CHAR, s[i]))
		{
			count++;
			c = s[i + 1];
			if (s[i] == c && c != '|')
			{
				printf("double token\n");
				i++;
			}
			printf("split char at: %s count: %d\n", &s[i], count);
		}
		i++;
	}
	return (count);
}

#include <string.h>
int	main(void)
{
	char	*input;
	// char	*word;

	while (1)
	{
		input = readline("debug> ");
		add_history(input);
		// printf("%d tokens\n", ft_count_tokens(input));
		// char **table = ft_split_tokens(input);
		// ft_print_strarr(table);
		// word = strtok(input, " \n");
		// while (word)
		// {
		// 	printf("%s$\n", word);
		// 	word = strtok(NULL, " \n");
		// }
		// printf("count luca: %d count tim: %d\n", count_tokens(input), ft_count_tokens_by_char(input));
		// ft_print_strarr(ft_split_tokens_by_char(input));
		// printf("trimmed: %s\n", trim_quotes(ft_strdup(input)));
		printf("count: %d\n", ft_count_words_keep(input));
		free(input);
	}
}
