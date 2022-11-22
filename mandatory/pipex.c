/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/22 17:16:57 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipefd[2];

	if (argc != 5)
		ft_error("Wrong number of argument");
	if (argc == 5)
		ft_are_args_ok(argc, argv);
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
		ft_error(argv[1]);
	fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
		ft_error(argv[4]); //argv[argc - 1];
	if (pipe(pipefd) < 0)
		ft_error("pipe error");
	
	return (0);
}
