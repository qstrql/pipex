/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/17 14:25:19 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	dup_and_close(int fd, int *pipefd, int process)
{
	if (process == 1)
	{
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(fd);
	}
	else if (process == 2)
	{
		dup2(fd, STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(fd);
	}
}

void	child_one(int *fd, int *pipefd, char **argv, char **envp)
{
	pid_t	pid;
	char 	*tmp;
	char	**cmd;

	pid = fork();
	if (pid < 0)
		is_error("Fork error");
	if (pid == 0)
	{
		fd[0] = open(argv[1], O_RDONLY);
		if (fd[0] < 0)
			is_error(argv[1]);
		cmd = ft_split(argv[2], ' ');
		tmp = path(envp, cmd[0]);
		if (cmd[0] != NULL && tmp)
		{
			dup_and_close(fd[0], pipefd, 1);
			execve(tmp, cmd, envp);
		}
		else
		{
			free(tmp);
			cant_find_cmd(fd[0], pipefd, cmd);
		}
	}
}

void	child_two(int *fd, int *pipefd, char **argv, char **envp)
{
	pid_t	pid;
	char 	*tmp;
	char	**cmd;

	pid = fork();
	if (pid < 0)
		is_error("Fork error");
	if (pid == 0)
	{
		fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			is_error(argv[4]);
		cmd = ft_split(argv[3], ' ');
		tmp = path(envp, cmd[0]);
		if (cmd[0] != NULL && tmp)
		{
			dup_and_close(fd[1], pipefd, 2);
			execve(tmp, cmd, envp);
		}
		else
		{
			free(tmp);
			cant_find_cmd(fd[1], pipefd, cmd);
		}
	}
}

void	pipex_process(int *fd, int *pipefd, char **argv, char **envp)
{
	child_one(fd, pipefd, argv, envp);
	child_two(fd, pipefd, argv, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipefd[2];

	if (argc != 5)
	{
		ft_putendl_fd("Wrong arguments, use ./pipex file1 cmd1 cmd2 file2", 2);
		return (0);
	}
	if (!envp || envp[0][0] == '\0')
		is_error("Envp error");
	if (pipe(pipefd) < 0)
		is_error("Pipefd error");
	pipex_process(fd, pipefd, argv, envp);
	return (0);
}
