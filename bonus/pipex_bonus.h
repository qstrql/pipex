/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:42 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/05 10:53:05 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/INCLUDES/libft.h"
#include <sys/stat.h> //open access
#include <fcntl.h> //open access
# include <unistd.h> //open close read write access dup dup2 execve fork pipe
# include <sys/types.h> //fork waitpid 
# include <sys/wait.h> // waitpid
# include <stdio.h> // perror
# include <errno.h> // perror 
# include <stdlib.h> // free
# include <string.h> // strerror

typedef struct s_pipex
{
	char	**envp;
	char	**argv;
	int		argc;
	int		nb_cmds;
	int		fd_io[2];
	int		*pipefd;
	int		*pid;
	char 	**cmd;
	char 	*path;
	int		idx;
}		t_pipex;
//paths_bonus.c
char	**get_paths(char **envp);
char	*path(char **envp, char *cmd);

//utils_bonus.c
void	is_error(char *str, t_pipex *d);
void	free_strs(char **strs);
void	cant_find_cmd(char **cmd);

#endif
