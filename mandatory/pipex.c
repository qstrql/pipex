/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/22 19:43:42 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open

void	ft_process_one(char **argv, char **envp, int *pipefd, int *fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		fd[0] = open(argv[1], O_RDONLY);
		if (fd[0] < 0)
			ft_error(argv[1]);
		//find cmd ??
		//exec cmd ??
		//close ??
	}
}

void	ft_process_two(char **argv, char **envp, int *pipefd, int *fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			ft_error(argv[4]);
		//find cmd ??
		//exec cmd ??
		//close ??
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipefd[2];
	int	status;

	errno = 0;
	if (argc != 5)
	{
		write(2, "Wrong arguments\n", 16);
		return (0);
	}
	if (pipe(pipefd) < 0)
		ft_error("pipe error");
	ft_process_one(argv, envp, pipefd, fd);	
	ft_process_two(argv, envp, pipefd, fd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
	return (0);
}



