/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:59:03 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/30 17:00:56 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <stdlib.h> //free
#include <sys/types.h> //ssize_t
#include <unistd.h> //read

static char	*ft_realloc(char *buf, char *line)
{
	char	*re_line;

	re_line = ft_strjoin(buf, line);
	free(buf);
	return (re_line);
}

static char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i += 1;
	line = ft_calloc(i + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_get_extra(char *str)
{
	int		i;
	int		len;
	char	*extra;

	len = ft_strlen(str);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	extra = ft_calloc((len - i) + 1, sizeof(char));
	i += 1;
	if (extra == NULL)
		return (NULL);
	len = 0;
	while (str[i + len] != '\0')
	{
		extra[len] = str[i + len];
		len++;
	}
	free(str);
	return (extra);
}

static char	*ft_reader(char *buf, int fd)
{
	char	*line;
	ssize_t	size_read;

	size_read = 1;
	if (buf == NULL)
		buf = ft_calloc(1, sizeof(char));
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	while (ft_strchr(buf, '\n') == 0 && size_read > 0)
	{
		size_read = read(fd, line, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		line[size_read] = '\0';
		buf = ft_realloc(buf, line);
	}
	free(line);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf[1024] = {NULL};

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = ft_reader(buf[fd], fd);
	if (buf[fd] == NULL)
		return (NULL);
	line = ft_get_line(buf[fd]);
	buf[fd] = ft_get_extra(buf[fd]);
	return (line);
}
