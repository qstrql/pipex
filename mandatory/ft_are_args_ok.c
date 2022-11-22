/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_are_args_ok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:39:36 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/22 11:45:14 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_verif_args(char *argv)
{

}

int	ft_space_only(char *argv)
{
	int		i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	ft_are_args_ok(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			ft_error();
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (ft_space_only(argv[i]) == 1)
			ft_error();
		ft_verif_args(argv[i]);
		i++;
	}
}
