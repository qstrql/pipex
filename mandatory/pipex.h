/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/01/17 12:50:51 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/INCLUDES/libft.h"
# include <sys/stat.h> //open access
# include <fcntl.h> //open access
# include <unistd.h> //open close read write access dup dup2 execve fork pipe
# include <sys/types.h> //fork waitpid 
# include <sys/wait.h> // waitpid
# include <stdio.h> // perror
# include <errno.h> // perror 
# include <stdlib.h> // free
# include <string.h> // strerror

//paths.c
char	**get_paths(char **envp);
char	*ft_realloc(char *joined, char *argv);
char	*path(char **envp, char *cmd);

//utils.c
void	is_error(char *str);
void	free_strs(char **strs);
void	cant_find_cmd(int fd, int *pipefd, char **cmd);

#endif
