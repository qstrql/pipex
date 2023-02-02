/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:11:16 by mjouot            #+#    #+#             */
/*   Updated: 2023/02/02 12:36:35 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

void	here_doc(char *delimiter, t_pipex *d)
{
	int		here_doc;
	char	*line;

	line = NULL;
	here_doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (here_doc < 0)
		is_error("heredoc error", d);
	while (1)
	{
		write(1, "here_doc > ", 11);
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, here_doc);
		free(line);
	}
	close(here_doc);
	d->fd[0] = open(".heredoc_tmp", O_RDONLY);
	if (d->fd[0] < 0)
	{
		unlink(".heredoc_tmp");
		is_error("heredoc error", d);
	}
}

int	check_heredoc(char *here_doc)
{
	if (here_doc && !ft_strncmp("here_doc", here_doc, 8))
		return (1);
	else
		return (0);
}
