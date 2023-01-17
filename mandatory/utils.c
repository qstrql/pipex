/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:40:05 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/17 12:45:53 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	is_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	cant_find_cmd(int fd, int *pipefd, char **cmd)
{	
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	free_strs(cmd);
	write(2, "Command not found\n", 18);
	exit(EXIT_FAILURE);
}
