/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:39:37 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/14 14:32:45 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stddef.h>

static size_t	ft_get_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			while (s[i] == c && s[i] != '\0')
				i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			word_count++;
		}
	}
	return (word_count);
}

static char	**ft_fill_strs(char const *s, char **strs, char sep)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] == sep && s[i] != '\0')
			i++;
		while (s[i + len] != sep && s[i + len] != '\0')
			len++;
		if (len > 0)
			strs[j++] = ft_substr(s, i, len);
		i += len;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (s == 0)
		return (0);
	strs = ft_calloc(ft_get_wordcount(s, c) + 1, sizeof(char *));
	if (strs == NULL)
		return (NULL);
	ft_fill_strs(s, strs, c);
	return (strs);
}
