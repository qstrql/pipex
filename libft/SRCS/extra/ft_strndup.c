/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:11:50 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/05 16:54:29 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stdlib.h>

char	*ft_strndup(char *src, size_t n)
{
	char		*dest;
	size_t		i;
	size_t		src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0' && src_len < n)
		src_len++;
	dest = ft_calloc(src_len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}	
	dest[i] = '\0';
	return (dest);
}
