/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:32:04 by tisabbat          #+#    #+#             */
/*   Updated: 2025/04/17 10:43:04 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags(const char *str, va_list args, unsigned int *counter)
{
	int	res_c;

	if (*str == 'c')
	{
		res_c = va_arg(args, int);
		*counter += write(1, (char *)&res_c, 1);
	}
	else if (*str == 'u')
		ft_put_unbr(va_arg(args, unsigned int), counter);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_pf(va_arg(args, int), counter);
	else if (*str == 's')
		ft_putstr_pf(va_arg(args, const char *), counter);
	else if (*str == 'x' || *str == 'X')
		ft_put_hex_or_ptr(va_arg(args, unsigned int), *str, counter, 0);
	else if (*str == 'p')
	{
		ft_put_hex_or_ptr(va_arg(args, unsigned long), 'x', counter, 1);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	result;

	if (!str)
		return (-1);
	i = 0;
	result = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				result += write(1, "%", 1);
			else
				flags(&str[i + 1], args, &result);
			i++;
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (result);
}
