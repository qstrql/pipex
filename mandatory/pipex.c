/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:30 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/01 21:14:24 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/stat.h> //open access
#include <fcntl.h> //open access
#include <unistd.h>

char	**get_paths(char **envp)
{
	int		i;
	char 	**paths;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	**paths;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	i = 0;
	paths = get_paths(envp);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, F_OK))
		{
			free_all(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_all(paths);
	return (0);
}

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
			execve(path(d->envp, cmd[0]), cmd, d->envp);
			free_all(cmd);
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
			execve(path(d->envp, cmd[0]), cmd, d->envp);
			free_all(cmd);
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

	d = ft_calloc(1, sizeof(t_pipex));
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
	d.pipefd = ft_calloc(d.nb_cmds - 1, sizeof(d.pipefd) * 2);
	if (!d.pipefd)
		is_error("Pipe error", &d);
	if (pipe(d.pipefd) < 0)
		is_error("Pipefd error", &d);
	d.pid[0] = 0;
	d.pid[1] = 0;
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
