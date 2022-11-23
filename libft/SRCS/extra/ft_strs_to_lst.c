/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:34:08 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/23 17:36:52 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"

t_list	*ft_strs_to_lst(char **strs)
{
	t_list	*lst;
	int		i;
	char	*str;

	str = ft_strdup(strs[0]);
	if (str == NULL)
		return (NULL);
	lst = ft_lstnew(str);
	i = 1;
	while (strs[i] != NULL)
	{
		str = ft_strdup(strs[i]);
		if (str == NULL)
			return (NULL);
		ft_lstadd_back(&lst, ft_lstnew(str));
		i++;
	}
	return (lst);
}
