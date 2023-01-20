/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/20 20:27:27 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(char *argv, t_pipex *d)
{
	int		here_doc;
	char	*buf;

	here_doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (here_doc < 0)
		is_error("heredoc error", &d);
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write(here_doc, buf, ft_strlen(buf));
		write(here_doc, "\n", 1);
		free(buf);
	}
	free(buf);
	close(here_doc);
	d.fd_io[0] = open(".heredoc_tmp", O_RDONLY);
	if (d->fd_io[0] < 0)
	{
		unlink(".heredoc_tmp");
		is_error("heredoc error", &d);
	}
}

int	check_heredoc(char *here_doc)
{
	if (here_doc && !ft_strncmp("here_doc", here_doc, 9))
		return (1);
	else
		return (0);
}

t_pipex	init(int argc, char **argv)
{
	t_pipex d;

	d.here_doc = check_heredoc(argv[1]);
	d.nb_cmds = argc - 3 - d.here_doc;
	if (d.here_doc == 1)
		here_doc(argv[2], &d)
	else
	{
		d.fd[0] = open(argv[1], O_RDONLY);
		if (d.fd[0] < 0)
				is_error("fd_io error", &d);
	}
	if (d.here_doc == 1)
		d.fd[1] = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
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
