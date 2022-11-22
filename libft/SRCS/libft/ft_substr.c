/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:39:00 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:38:17 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stddef.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		s_len;
	char		*out;

	i = 0;
	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	else if (s_len == len && len == start + 1)
		len = 1;
	if (start > s_len)
		return (out = ft_calloc(1, sizeof(char)));
	out = ft_calloc(len + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && start <= ft_strlen(s))
	{
		out[i] = s[start + i];
		i++;
	}
	return (out);
}
