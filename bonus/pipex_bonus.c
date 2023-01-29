/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/29 23:36:08 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

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

void	even_or_odd(t_pipex *d)
{
	if (d->idx % 2 == 0)
	{
		close(d->pipeA[READ]);
		close(d->pipeB[WRITE]);
		dup2(d->pipeA[READ], STDIN_FILENO);
    	dup2(d->pipeB[WRITE], STDOUT_FILENO);
	}
	else if (d->idx % 2 != 0)
	{
		close(d->pipeB[READ]);
		close(d->pipeA[WRITE]);
		dup2(d->pipeB[READ], STDIN_FILENO);
		dup2(d->pipeA[WRITE], STDOUT_FILENO);
	}
}

void	redirect_io(t_pipex *d)
{
	if (d->idx == 0)
	{
		close(d->pipeB[WRITE]);
		dup2(d->pipeB[WRITE], STDOUT_FILENO);
	}
	else if (d->idx == d->nb_cmds)
	{
		if (d->idx % 2 == 0)
		{	
			close(d->pipeB[WRITE]);
			dup2(d->pipeB[READ], STDIN_FILENO);
		}
		else
		{	    
			close(d->pipeA[WRITE]);
			dup2(d->pipeA[READ], STDIN_FILENO); 
		}
	}
	else
		even_or_odd(d);
}

void	child(t_pipex *d, char **envp)
{
	redirect_io(d);
	if (d->cmd[0] != NULL && d->path)
		execve(d->path, d->cmd, envp);
	else
	 	cant_find_cmd(cmd, d);
}

void	start_process(t_pipex *d, char **argv, char **envp)
{
	pid_t pid;

	while (d->idx < d->nb_cmds)
	{
		if (d->idx % 2 == 0)
			if (pipe(d->pipeB) < 0)
				is_error("Pipefd error", d);
		if (d->idx % 2 != 0)
			if (pipe(d->pipeA) < 0)
				is_error("Pipefd error", d);
		d->cmd = ft_split(argv[d->idx + 2 + d->here_doc], ' ');
		d->path = path(envp, d->cmd[0]);
		pid = fork();
		if (pid < 0)
			is_error("Fork error", d);
		else if (pid == 0)
			child(d, envp);
		waitpid(pid, NULL, 0);
		free_strs(d->cmd);
		free(d->path);
		d->idx++;
	}
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
