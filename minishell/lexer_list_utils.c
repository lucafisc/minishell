#include "minishell.h"

t_lexer	*ft_dbllstnew(char *data, int info, int index)
{
	t_lexer	*new;

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

void	ft_dbllst_addback(t_lexer **list, t_lexer *new)
{
	t_lexer	*cur;

	if (!new)
		return ;
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	new->next = NULL;
}

t_lexer *new_lexer_list_from_matrix(char **matrix)
{
	t_lexer	*new;
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (i == 0)
			new = ft_dbllstnew(matrix[i], 1, i);
		else
			ft_dbllst_addback(&new, ft_dbllstnew(matrix[i], 1, i));
			i++;
	}
	return (new);
}

void print_list(t_lexer **list)
{
	t_lexer *cur;

	cur = *list;
	while (cur)
	{
		printf("node %d:%s\n", cur->index, cur->data);
		cur = cur->next;
	}
}

void	free_lexer_list(t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*temp;

	cur = *list;
	while (cur)
	{
		temp = cur;
		free(temp->data);
		free(temp);
		cur = cur->next;
	}
	cur = NULL;
}