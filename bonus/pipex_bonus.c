/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/05 11:04:05 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void redirect_io(t_pipex *d)
{
	if (d->idx == 1)
	{
		dup2(d->fd_io[0], STDIN_FILENO);
		dup2(d->pipefd[1], STDOUT_FILENO);
	}
	else if (d->idx == d->nb_cmds - 1)
	{
		dup2(d->fd_io[1], STDOUT_FILENO);
		dup2(d->pipefd[0], STDIN_FILENO);
	}
	else
		dup2();
		dup2();
}

void	child(t_pipex *d)
{
		redirect_io(d);
		close(d->pipefd[1]);
		close(d->fd_io[0]);
		if (!execve(d->path, d->cmd, d->envp))
			cant_find_cmd(d->cmd);
}

int	start_process(t_pipex *d)
{
	if (pipe(d->pipefd) == -1)
		is_error("pipefd error", d);
	while (d->idx < d->nb_cmds)
	{
		d->cmd = ft_split(d->argv[d->idx + 2], ' ');
		d->path = path(d->envp, d->cmd[d->idx + 2]);
		d->pid[d->idx] = fork();
		if (d->pid[d->idx] == 0)
			child(d);
		free_strs(d->cmd);
		free(d->path);
		d->idx++;
	}
}

t_pipex	init(int argc, char **argv, char **envp)
{
	t_pipex d;

	d.argc = argc;
	d.argv = argv;
	d.envp = envp;
	d.nb_cmds = argc - 3;
	d.fd_io[0] = open(d.argv[1], O_RDONLY);
	if (d.fd_io[0] < 0)
			is_error("fd_io error", &d);
	d.fd_io[1] = open(d.argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.fd_io[1] < 0)
			is_error("fd_io error", &d);
	ft_bzero(d.pipefd, 2);
	if (pipe(d.pipefd) < 0)
		is_error("Pipefd error", &d);
	ft_bzero(d.pid, 2);
	d.idx = 0;
	
	return (d);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex d;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong arguments, use ./pipex file1 cmd1 cmd2 file2", 2);
		return (0);
	}
	if (!envp || envp[0][0] == '\0')
		is_error("Envp error", &d);
	d = init(argc, argv, envp);
	start_process(&d);
	return (0);
}
