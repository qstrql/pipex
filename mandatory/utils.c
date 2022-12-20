/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:40:05 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/20 11:40:05 by mjouot           ###   ########.fr       */
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

void	is_error(char *str, t_pipex *d)
{
	close(d->fd_io[0]);
	close(d->fd_io[1]);
	close(d->pipefd[0]);
	close(d->pipefd[1]);
	perror(str);
	exit(EXIT_FAILURE);
}

void	cant_find_cmd(char **cmd, t_pipex *d)
{
	free_strs(cmd);
	is_error("Command not found", d);
}
