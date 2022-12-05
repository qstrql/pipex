/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/05 13:48:16 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_two(t_pipex *d)
{
	char 	**cmd;

	d->pid[1] = fork();
	if (d->pid[1] < 0)
		is_error("fork", d);
	if (d->pid[1] == 0)
	{
		cmd = ft_split(d->argv[3], ' ');
		close(d->pipefd[1]);
		dup2(d->fd_io[1], STDOUT_FILENO);
		dup2(d->pipefd[0], STDIN_FILENO);
		if (cmd[0] != NULL && path(d->envp, cmd[0]))
		{
			close(d->pipefd[0]);
			close(d->fd_io[1]);
			execve(path(d->envp, cmd[0]), cmd, d->envp);
			free_strs(cmd);
		}
		else
			write(2, "Command not found\n", 18);
	}
}

void	child_one(t_pipex *d)
{
	char 	**cmd;

	d->pid[0] = fork();
	if (d->pid[0] < 0)
		is_error("fork", d);
	if (d->pid[0] == 0)
	{
		cmd = ft_split(d->argv[2], ' ');
		close(d->pipefd[0]);
		dup2(d->fd_io[0], STDIN_FILENO);
		dup2(d->pipefd[1], STDOUT_FILENO);
		if (cmd[0] != NULL && path(d->envp, cmd[0]))
		{
			close(d->pipefd[1]);
			close(d->fd_io[0]);
			execve(path(d->envp, cmd[0]), cmd, d->envp);
			free_strs(cmd);
		}
		else
			cant_find_cmd(cmd);
	}
}

void parent(t_pipex *d)
{
	int	status;

	child_one(d);
	child_two(d);
	close(d->pipefd[0]);
	close(d->pipefd[1]);
	waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
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
	parent(&d);
	return (0);
}
