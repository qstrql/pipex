/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/13 13:14:03 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	child_two(t_pipex *d)
{
	char	**cmd;

	cmd = ft_split(d->argv[3], ' ');
	close(d->pipefd[1]);
	dup2(d->fd_io[1], STDOUT_FILENO);
	dup2(d->pipefd[0], STDIN_FILENO);
	close_fd(d);
	if (cmd[0] != NULL && path(d->envp, cmd[0]))
		execve(path(d->envp, cmd[0]), cmd, d->envp);
	else
		cant_find_cmd(cmd);
	free_strs(cmd);
	exit(EXIT_FAILURE);
}

void	child_one(t_pipex *d)
{
	char	**cmd;

	cmd = ft_split(d->argv[2], ' ');
	dup2(d->fd_io[0], STDIN_FILENO);
	dup2(d->pipefd[1], STDOUT_FILENO);
	close_fd(d);
	if (cmd[0] != NULL && path(d->envp, cmd[0]))
		execve(path(d->envp, cmd[0]), cmd, d->envp);
	else
		cant_find_cmd(cmd);
	free_strs(cmd);
	exit(EXIT_FAILURE);
}

void	parent(t_pipex *d)
{
	pid_t child1;
	pid_t child2;

	child1 = fork();
	if (child1 < 0)
		is_error("fork", d);
	if (child1 == 0)
		child_one(d);
	child2 = fork();
	if (child2 < 0)
		is_error("fork", d);
	if (child2 == 0)
		child_two(d);
	close_fd(d);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

t_pipex	init(int argc, char **argv, char **envp)
{
	t_pipex	d;

	d.argc = argc;
	d.argv = argv;
	d.envp = envp;
	d.nb_cmds = argc - 3;
	d.fd_io[0] = open(d.argv[1], O_RDONLY);
	if (d.fd_io[0] < 0)
	{
		perror("fd io error ");
		exit(EXIT_FAILURE);
	}	
	d.fd_io[1] = open(d.argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.fd_io[1] < 0)	
	{
		close(d.fd_io[0]);
		perror("fd io error ");
		exit(EXIT_FAILURE);
	}	
	if (pipe(d.pipefd) < 0)
		is_error("Pipefd error", &d);
	d.idx = 0;
	return (d);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	d;

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
