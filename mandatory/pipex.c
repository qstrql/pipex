/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/24 17:09:49 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipefd[2];

	if (argc != 5)
	{
		write(2, "Wrong arguments\n", 16);
		return (0);
	}
	if (pipe(pipefd) < 0)
		ft_error("pipe error");
	ft_start_processes(argv, envp, pipefd, fd);
	return (0);
}
