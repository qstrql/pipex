/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:40:05 by mjouot            #+#    #+#             */
/*   Updated: 2023/02/02 11:19:00 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	(void)d;
	perror(str);
	close_all(d);
	exit(EXIT_FAILURE);
}

void	cant_find_cmd(char **cmd, t_pipex *d)
{	
	free_strs(cmd);
	write(2, "Command not found\n", 18);
	close_all(d);
	exit(EXIT_FAILURE);
}

void	closefd(t_pipex *d)
{
	if (d->idx == 0)
	{
		close(d->fd[0]);
		close(d->pipe_b[WRITE]);
	}
	else if (d->idx == d->nb_cmds)
	{
		close(d->fd[1]);
		if (d->idx % 2 == 0)
			close(d->pipe_b[WRITE]);
		else
			close(d->pipe_a[WRITE]); 
	}
	else if (d->idx % 2 == 0)
	{
		close(d->pipe_a[READ]);
    	close(d->pipe_b[WRITE]);
	}
	else if (d->idx % 2 != 0)
	{
		close(d->pipe_b[READ]);
		close(d->pipe_a[WRITE]);
	}
}

void	close_all(t_pipex *d)
{
	if (d->idx > 1)
	{
		if (d->pipe_a[READ] != -1)
			close(d->pipe_a[READ]);
		if (d->pipe_a[WRITE] != -1)
			close(d->pipe_a[WRITE]);
		if (d->pipe_b[READ] != -1)
			close(d->pipe_b[READ]);
		if (d->pipe_b[WRITE] != -1)
			close(d->pipe_b[WRITE]);
		if (d->fd[0] != -1)
			close(d->fd[0]);
		if (d->fd[1] != -1)
			close(d->fd[1]);
	}
	else
	{
		close(d->pipe_b[READ]);
		close(d->pipe_b[WRITE]);
		if (d->fd[0] != -1)
			close(d->fd[0]);
		if (d->fd[1] != -1)
			close(d->fd[1]);
	}
}
