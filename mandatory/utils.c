/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:40:05 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/01 21:22:49 by mjouot           ###   ########.fr       */
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
	int	i;

	i = 0;
	if (d)
	{	
		while (i < (d->nb_cmds - 1) * 2)
			close(d->pipefd[i++]);
		if (d->fd_io[0] != -1)
		close(d->fd_io[0]);
		if (d->fd_io[1] != -1)
		close(d->fd_io[1]);
	}
	perror(str);
	exit(EXIT_FAILURE);
}

void	cant_find_cmd(char **cmd)
{
	write(2, "Command not found\n", 18);
	free_strs(cmd);
	exit(EXIT_FAILURE);
}
