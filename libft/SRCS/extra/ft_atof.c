/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:21:01 by mjouot            #+#    #+#             */
/*   Updated: 2022/12/09 18:20:00 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"

static int	ft_skip_space_and_sign(const char *nptr, int *sign)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

double	ft_atof(const char *nptr)
{
	int		i;
	int		sign;
	double	nb;
	double	div;

	nb = 0;
	sign = 1;
	div = 0.1;
	i = ft_skip_space_and_sign(nptr, &sign);
	while (nptr[i] && ft_isdigit(nptr[i]) && nptr[i] != '.')
	{
		nb = (nb * 10.0) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
		i++;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nb = nb + ((nptr[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (nptr[i] && !ft_isdigit(nptr[i]))
		return (-1);
	return (nb * sign);
}
