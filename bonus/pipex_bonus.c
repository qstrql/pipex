/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/07 15:52:00 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>
#include <unistd.h>

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
		dup2(d->pipefd[d->idx - 1], STDIN_FILENO);
		dup2(d->pipefd[d->idx], STDOUT_FILENO);
		
		
}

void	child(t_pipex *d, char **envp)
{
		redirect_io(d);
		close(d->pipefd[1]);
		close(d->fd_io[0]);
		if (!execve(d->path, d->cmd, envp))
			cant_find_cmd(d->cmd);
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

void	wait_for_child(t_pipex *d)
{
	int	status;
	pid_t wait_for;

	d->idx -= 1;
	while (d->idx >= 0)
	{
		wait_for = waitpid(d->pid[d->idx], &status, 0);
		if (wait_for < 0)
			is_error("waitpid error", d);
		d->idx--;
	}
	free(d->pipefd);
	free(d->pid);
}

void	link_pipes(t_pipex *d)
{
	int	i;

	i = 0;
	while (i < d->nb_cmds - 1)
	{
		if (pipe(d->pipefd + 2 * i) < 0)
			is_error("pipefd linking error", d);
		i++;
	}
}

t_pipex	init(int argc, char **argv)
{
	t_pipex d;

	d.nb_cmds = argc - 3;
	d.fd_io[0] = open(argv[1], O_RDONLY);
	if (d.fd_io[0] < 0)
			is_error("fd_io error", &d);
	d.fd_io[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.fd_io[1] < 0)
			is_error("fd_io error", &d);
	d.pipefd = ft_calloc(d.nb_cmds - 1, sizeof(d.pipefd) * 2);
	if (!d.pipefd)
		is_error("pipefd error", &d);
	d.pid = ft_calloc(d.nb_cmds - 1, sizeof(d.pid));
	if (!d.pid)
		is_error("pid error", &d);
	link_pipes(&d);
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
	wait_for_child(&d);
	return (0);
}
