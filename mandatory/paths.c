/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:23:18 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/10 18:09:38 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

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
		if (access(path, F_OK) == 0)
		{
			free_strs(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_strs(paths);
	return (0);
}
