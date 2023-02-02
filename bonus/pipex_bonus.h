/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/02/02 11:18:23 by mjouot           ###   ########.fr       */
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

# define READ 0
# define WRITE 1

typedef struct s_pipex
{
	int		nb_cmds;
	int		fd[2];
	int		pipe_a[2];
	int		pipe_b[2];
	int		here_doc;
	pid_t	pid;
	char 	**cmd;
	char 	*path;
	int		idx;
}		t_pipex;

//here_doc_bonus.c
void	here_doc(char *delimiter, t_pipex *d);
int		check_heredoc(char *here_doc);

//paths_bonus.c
char	**get_paths(char **envp);
char	*path(char **envp, char *cmd);

//utils_bonus.c
void	is_error(char *str, t_pipex *d);
void	free_strs(char **strs);
void	cant_find_cmd(char **cmd, t_pipex *d);
void	close_all(t_pipex *d);
void	closefd(t_pipex *d);

#endif
