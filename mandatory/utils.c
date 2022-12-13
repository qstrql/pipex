/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:40:05 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/13 12:55:26 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	close_fd(t_pipex *d)
{
	if (d->fd_io[0] != -1)
		close(d->fd_io[0]);
	if (d->fd_io[1] != -1)
		close(d->fd_io[1]);
	if (d->pipefd[0] != -1)
		close(d->fd_io[0]);
	if (d->pipefd[1] != -1)
		close(d->fd_io[1]);
}

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
	if (d->pipefd[0] != -1)
		close(d->fd_io[0]);
	if (d->pipefd[1] != -1)
		close(d->fd_io[1]);
	if (d->fd_io[0] != -1)
		close(d->fd_io[0]);
	if (d->fd_io[1] != -1)
		close(d->fd_io[1]);
	perror(str);
	exit(EXIT_FAILURE);
}

void	cant_find_cmd(char **cmd)
{
	write(2, "Command not found\n", 18);
	free_strs(cmd);
	exit(EXIT_FAILURE);
}
