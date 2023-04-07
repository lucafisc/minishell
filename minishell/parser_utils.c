#include "minishell.h"

t_command	*ft_new_cmd_list(char **cmd)
{
	t_command	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
		
	new->data = ft_strdup(data);
	new->info = info;
	new->pipe = 0;
	new->prev = NULL;
	new->next = NULL;
	new->index = index;
	return (new);
}