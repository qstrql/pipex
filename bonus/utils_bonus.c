/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:40:05 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/17 15:14:23 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	is_error(char *str, t_pipex *d)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	cant_find_cmd(char **cmd, t_pipex *d)
{	
	free_strs(cmd);
	write(2, "Command not found\n", 18);
	exit(EXIT_FAILURE);
}
