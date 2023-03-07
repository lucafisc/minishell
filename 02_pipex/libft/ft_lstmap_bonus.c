/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:16:57 by tfregni           #+#    #+#             */
/*   Updated: 2022/12/02 15:36:05 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*cursor_new;
	t_list	*cursor_old;

	if (lst->content)
		new_lst = ft_lstnew((*f)(lst->content));
	if (!lst || !new_lst)
		return (NULL);
	cursor_new = new_lst;
	cursor_old = lst->next;
	while (cursor_old)
	{
		cursor_new->next = ft_lstnew((*f)(cursor_old->content));
		if (!cursor_new->next)
		{
			ft_lstclear(&cursor_new, del);
			return (NULL);
		}
		cursor_old = cursor_old->next;
		cursor_new = cursor_new->next;
	}
	return (new_lst);
}
