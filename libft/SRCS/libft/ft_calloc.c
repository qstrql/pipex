/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:43:43 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:38:44 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	fullsize;
	void	*mem;

	if (nmemb > 2147483647 || size > 2147483647)
		return ((void *)0);
	fullsize = size * nmemb;
	if (fullsize > 2147483647)
		return ((void *)0);
	mem = malloc(fullsize);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, fullsize);
	return (mem);
}
