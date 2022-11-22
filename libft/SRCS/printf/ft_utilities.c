/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:40:20 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/30 17:04:37 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/ft_printf.h"
#include <unistd.h>

int	ft_putchar_r(const char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_r(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (s != 0)
		while (s[i] != '\0')
			i++;
	write(1, s, i);
	return (i);
}

int	ft_strlen_printf(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
