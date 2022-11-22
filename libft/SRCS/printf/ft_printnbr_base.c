/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:37:09 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/30 17:06:37 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include "../../INCLUDES/ft_printf.h"
#include <unistd.h>

static int	ft_getcount_hexa(unsigned long n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	ft_usign_putnbr_base(unsigned int n, const char *base)
{
	unsigned int	last_n;

	if (n == 0)
		ft_putchar(base[0]);
	if (n != 0)
	{
		last_n = n % ft_strlen_printf(base);
		n = n / ft_strlen_printf(base);
		if (n != 0)
			ft_usign_putnbr_base(n, base);
		ft_putchar(base[last_n]);
	}
}

static void	ft_long_putnbr_base(unsigned long n, const char *base)
{
	int	last_n;

	if (n == 0)
		ft_putchar(base[0]);
	if (n != 0)
	{
		last_n = n % ft_strlen_printf(base);
		n = n / ft_strlen_printf(base);
		if (n != 0)
			ft_long_putnbr_base(n, base);
		ft_putchar(base[last_n]);
	}
}

int	ft_printnbr_base(unsigned long n, const char *base, char c)
{
	int	count;

	count = ft_getcount_hexa(n);
	if (c == 'x' || c == 'X')
		ft_usign_putnbr_base(n, base);
	if (c == 'p')
	{
		if (n == 0)
		{
			write(1, "(nil)", 5);
			return (5);
		}
		write(1, "0x", 2);
		count += 2;
		ft_long_putnbr_base(n, base);
	}
	return (count);
}
