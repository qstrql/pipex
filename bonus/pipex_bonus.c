/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/24 15:14:45 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex	init(int argc, char **argv)
{
	t_pipex d;

	d.here_doc = check_heredoc(argv[1]);
	d.nb_cmds = argc - 3 - d.here_doc;
	if (d.here_doc == 1)
		here_doc(argv[2], &d);
	else
	{
		d.fd[0] = open(argv[1], O_RDONLY);
		if (d.fd[0] < 0)
				is_error("infile error", &d);
	}
	if (d.here_doc == 1)
		d.fd[1] = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		d.fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.fd[1] < 0)
			is_error("outfile error", &d);
	d.idx = 0;
	return (d);
}

void	start_process(t_pipex *d, char **argv, char **envp)
{
	
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
