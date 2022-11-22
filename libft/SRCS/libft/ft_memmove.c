/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:41:37 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:32:30 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_copy;
	unsigned char	*src_copy;

	i = 0;
	if (dest == 0 && src == 0)
		return ((void *)0);
	dest_copy = (unsigned char *)dest;
	src_copy = (unsigned char *)src;
	if (n == 0)
		return (dest);
	if (src_copy > dest_copy)
		ft_memcpy(dest, src, n);
	else
	{
		while (i < n)
		{
			dest_copy[n - i - 1] = src_copy[n - i - 1];
			i++;
		}
	}
	return (dest);
}
