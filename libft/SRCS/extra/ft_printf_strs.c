/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:23:50 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/31 14:00:28 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/ft_printf.h"
#include "../../INCLUDES/libft.h"
#include <unistd.h>

void	ft_printf_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		ft_printf("strs[%d] : %s\n", i, strs[i]);
		i++;
	}
	write(1, "\n", 1);
}
