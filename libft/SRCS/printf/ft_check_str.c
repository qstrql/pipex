/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:29:48 by mjouot            #+#    #+#             */
/*   Updated: 2022/11/14 22:44:26 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_conversion(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		return (ft_putchar_r(va_arg(args, int)));
	else if (c == 's')
		count = ft_putstr_r(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count = ft_printnbr(va_arg(args, int), c);
	else if (c == 'u')
		count = ft_printnbr(va_arg(args, unsigned int), c);
	return (count);
}

static int	ft_conversion_hexa(char c, va_list args)
{
	int			count;
	const char	*hexa_lower = "0123456789abcdef";
	const char	*hexa_upper = "0123456789ABCDEF";

	count = 0;
	if (c == 'p')
		count = ft_printnbr_base(va_arg(args, unsigned long), hexa_lower, c);
	else if (c == 'x')
		count = ft_printnbr_base(va_arg(args, unsigned int), hexa_lower, c);
	else if (c == 'X')
		count = ft_printnbr_base(va_arg(args, unsigned int), hexa_upper, c);
	else if (c == '%')
		return (ft_putchar_r('%'));
	return (count);
}

static int	ft_conversion_count(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'u')
		count += ft_conversion(c, args);
	else if (c == 'p' || c == 'x' || c == 'X' || c == '%')
		count += ft_conversion_hexa(c, args);
	else
	{
		ft_putchar_r('%');
		ft_putchar_r(c);
	}
	return (count);
}

int	ft_check_str(const char *str, va_list args)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			c = str[i + 1];
			count += ft_conversion_count(c, args);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	return (count);
}
