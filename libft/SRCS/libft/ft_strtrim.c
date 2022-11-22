/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:39:27 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:35:09 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stddef.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	word_len;
	char	*s1_copy;

	start = 0;
	if (s1 == 0 || set == 0)
		return (0);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) != 0 && end > start)
		end--;
	word_len = end - start + 1;
	s1_copy = ft_calloc(word_len, sizeof(char));
	if (s1_copy == NULL)
		return (NULL);
	ft_strlcpy(s1_copy, &s1[start], word_len);
	return (s1_copy);
}
