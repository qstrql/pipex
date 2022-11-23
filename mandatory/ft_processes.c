/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:51:34 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/23 20:34:40 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/stat.h> //open access
#include <fcntl.h> //open access
#include <unistd.h>

char	**ft_get_paths(char **envp)
{
	int		i;
	char 	**paths;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*ft_path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	**paths;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	i = 0;
	paths = ft_get_paths(envp);
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

void	ft_process_one(char **argv, char **envp, int *pipefd, int *fd)
{
	char 	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		fd[0] = open(argv[1], O_RDONLY);
		if (fd[0] < 0)
			ft_error(argv[1]);
		cmd = ft_split(argv[2], ' ');
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		if (cmd[0] != NULL && ft_path(envp, cmd[0]))
		{
			execve(ft_path(envp, cmd[0]), cmd, envp);
			free_all(cmd);
		}
		else
			ft_cant_find_cmd(cmd);
	}
}

void	ft_process_two(char **argv, char **envp, int *pipefd, int *fd)
{
	char 	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			ft_error(argv[4]);
		cmd = ft_split(argv[3], ' ');
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (cmd[0] != NULL && ft_path(envp, cmd[0]))
		{
			execve(ft_path(envp, cmd[0]), cmd, envp);
			free_all(cmd);
		}
		else
			write(2, "Command not found\n", 18);
	}
}
