#include "minishell.h"

t_bool	is_not_escaped(int i, char *s)
{
	if (i == 0 || s[i - 1] != '\\')
		return (true);
	else
		return (false);
}

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

void	fill_lexer_list(t_lexer **node, char *data, int info, int i)
{
	if (i == 0)
		*node = ft_dbllstnew(data, info, i);
	else
		ft_dbllst_addback(node, ft_dbllstnew(data, info, i));
}

t_lexer *new_lexer_list_from_matrix(char **matrix)
{
	t_lexer	*new;
	int		i;

	i = 0;
	while (matrix[i])
	{
		fill_lexer_list(&new, matrix[i], 1, i);
		i++;
	}
	return (new);
}

void print_list(t_lexer *list)
{
	while (list)
	{
		printf("node %d:%s\n", list->index, list->data);
		list = list->next;
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
		cur = cur->next;
		free(temp->data);
		free(temp);
	}
}
