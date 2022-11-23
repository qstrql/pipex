/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/23 20:13:01 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipefd[2];
	int	status;

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
    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
	return (0);
}



