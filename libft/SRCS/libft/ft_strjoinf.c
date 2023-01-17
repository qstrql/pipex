/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:39:14 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/17 14:21:39 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stdlib.h>

static char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	dest_len;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strjoinf(char *s1, char *s2)
{
	int		len;
	char	*strs;

	if (s1 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	strs = ft_calloc(len + 1, sizeof(char));
	if (strs == NULL)
		return (NULL);
	strs = ft_strcat(strs, (char *)s1);
	strs = ft_strcat(strs, (char *)s2);
	free(s1);
	return (strs);
}
