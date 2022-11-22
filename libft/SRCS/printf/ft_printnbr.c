/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:41:11 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/14 22:45:02 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/ft_printf.h"
#include <unistd.h>

static int	ft_getcount(long n, char c)
{
	int		i;

	i = 0;
	if (c == 'i' || c == 'd')
	{
		n = (int)n;
		if (n <= 0)
			i++;
		while (n != 0)
		{
			n /= 10;
			i++;
		}
		return (i);
	}
	n = (unsigned int)n;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_usign_putnbr(unsigned int n)
{
	if (n >= 10)
	{
		ft_usign_putnbr(n / 10);
		ft_usign_putnbr(n % 10);
	}
	else
	{
		n += '0';
		write(1, &n, 1);
	}
}

static void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		n += '0';
		write(1, &n, 1);
	}
}

int	ft_printnbr(int n, char c)
{
	int	count;

	count = 0;
	if (c == 'i' || c == 'd')
	{
		ft_putnbr(n);
		count = ft_getcount(n, c);
	}
	else if (c == 'u')
	{
		ft_usign_putnbr(n);
		count = ft_getcount(n, c);
	}
	return (count);
}
