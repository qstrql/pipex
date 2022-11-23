/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:15:42 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/23 16:20:32 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/INCLUDES/libft.h"
# include <unistd.h> //open close read write access dup dup2 execve fork pipe
# include <sys/types.h> //fork waitpid 
# include <sys/wait.h> // waitpid
# include <stdio.h> // perror
# include <errno.h> // perror 
# include <stdlib.h> // free
# include <string.h> // strerror

//ft_utils.c
void	ft_error(char *str);
void	free_all(char **splitted);

//ft_processes.c
char	**ft_get_paths(char **envp);
char	*ft_path(char **envp, char *cmd);
void	ft_process_one(char **argv, char **envp, int *pipefd, int *fd);
void	ft_process_two(char **argv, char **envp, int *pipefd, int *fd);

#endif
