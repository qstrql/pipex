/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:27:20 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:41:02 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*mapped_lst;

	if (!lst || !f || !del)
		return (NULL);
	mapped_lst = NULL;
	while (lst != NULL)
	{
		node = ft_lstnew((*f)(lst->content));
		if (node == NULL)
		{
			ft_lstclear(&mapped_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&mapped_lst, node);
		lst = lst->next;
	}
	return (mapped_lst);
}
