/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/19 16:30:29 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>
#include <unistd.h>

void redirect_io(t_pipex *d)
{
	if (d->idx = 0)
	{	
		dup2(d->fd, STDIN_FILENO);
		dup2(d->pipefd[1], STDOUT_FILENO);
	}
	else if (d->idx = d->nb_cmds)
	{
		dup2(d->fd, STDOUT_FILENO);
		dup2(d->pipefd[0], STDIN_FILENO);
	}
	else 
	{
			
	}
}

void	child(t_pipex *d, char **envp)
{
	redirect_io(d);
	if (d->cmd[0] != NULL && d->path)
		execve(d->path, d->cmd, envp);
	else
		cant_find_cmd(d->cmd, d);
}

void	start_process(t_pipex *d, char **argv, char **envp)
{
	if (pipe(d->pipefd) == -1)
		is_error("pipefd error", d);
	while (d->idx < d->nb_cmds)
	{
		d->cmd = ft_split(argv[d->idx + 2], ' ');
		d->path = path(envp, d->cmd[d->idx + 2]);
		d->pid[d->idx] = fork();
		if (d->pid[d->idx] == 0)
			child(d, envp);
		free_strs(d->cmd);
		free(d->path);
		d->idx++;
	}
}

t_pipex	init(int argc, char **argv)
{
	t_pipex d;

	d.nb_cmds = argc - 3;
	d.fd[0] = open(argv[1], O_RDONLY);
	if (d.fd[0] < 0)
			is_error("fd_io error", &d);
	d.fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.fd[1] < 0)
			is_error("fd_io error", &d);
	d.pid = ft_calloc(d.nb_cmds - 1, sizeof(d.pid));
	if (!d.pid)
		is_error("pid error", &d);
	d.idx = 0;
	return (d);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex d;

	if (argc < 5)
	{
		ft_putendl_fd
			("Wrong arguments, use ./pipex file1 cmd1 cmd2 ... file2", 2);
		return (0);
	}
	if (!envp || envp[0][0] == '\0')
		is_error("Envp error", &d);
	d = init(argc, argv);
	start_process(&d, argv, envp);
	return (0);
}
