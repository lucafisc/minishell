#include "minishell.h"

int	count_words_keep(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			i++;
		}
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

size_t	str_siz_keep(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split_keep(char const *s, char c)
{
	int		words;
	char	**arr;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	words = count_words_keep(s, c);
	write(1, "hi\n", 3);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			arr[j] = calloc(2, sizeof(char));
			arr[j][0] = c;
			i++;
			j++;
		}
		else
		{
			len = str_siz_keep((s + i), c);
			arr[j] = ft_substr(s, i, len);
			j++;
			i += len;
		}
	}
	arr[j] = NULL;
	return (arr);
}
