#include "libft.h"

int	ft_is_escaped(int i, char *s)
{
	if (i == 0 || s[i - 1] != '\\')
		return (0);
	else
		return (1);
}