/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:24:01 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:41:59 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stdlib.h>

void	ft_lstadd_front(t_list **lst, t_list *new_list)
{
	if (new_list != NULL)
	{
		new_list->next = *lst;
		*lst = new_list;
	}
}
