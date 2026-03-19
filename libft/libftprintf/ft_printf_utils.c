/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:29:02 by tisabbat          #+#    #+#             */
/*   Updated: 2025/04/17 11:03:29 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_pf(const char *s)
{
	int	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

void	ft_putstr_pf(const char *s, unsigned int *counter)
{
	if (!s)
	{
		*counter += write(1, "(null)", 6);
		return ;
	}
	*counter += write(1, s, ft_strlen_pf(s));
}

void	ft_putnbr_pf(int n, unsigned int *counter)
{
	char	res;

	if (n == -2147483648)
	{
		ft_putnbr_pf(n / 10, counter);
		*counter += write(1, "8", 1);
	}
	else if (n < 0)
	{
		*counter += write(1, "-", 1);
		ft_putnbr_pf(-n, counter);
	}
	else
	{
		if (n > 9)
			ft_putnbr_pf(n / 10, counter);
		res = (n % 10) + '0';
		*counter += write(1, &res, 1);
	}
}

void	ft_put_unbr(unsigned int n, unsigned int *counter)
{
	char	res;

	if (n > 9)
		ft_put_unbr(n / 10, counter);
	res = (n % 10) + '0';
	*counter += write(1, &res, 1);
}

void	ft_put_hex_or_ptr(unsigned long hex, char uppercase,
							unsigned int *counter, bool is_ptr)
{
	char	*alpha;

	if (uppercase == 'X')
		alpha = "ABCDEF";
	else
		alpha = "abcdef";
	if (is_ptr)
	{
		if (hex == 0)
		{
			*counter += write(1, "(nil)", 5);
			return ;
		}
		else
			*counter += write(1, "0x", 2);
	}
	if (hex >= 16)
		ft_put_hex_or_ptr(hex / 16, uppercase, counter, 0);
	if ((hex % 16) < 10)
		*counter += write(1, &"0123456789"[hex % 16], 1);
	else
		*counter += write(1, &alpha[hex % 16 - 10], 1);
}
