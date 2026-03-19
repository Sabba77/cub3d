/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:31:33 by tisabbat          #+#    #+#             */
/*   Updated: 2025/04/17 10:42:02 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>

int		ft_strlen_pf(const char *s);
void	ft_putstr_pf(const char *s, unsigned int *counter);
void	ft_putnbr_pf(int n, unsigned int *counter);
void	ft_put_unbr(unsigned int n, unsigned int *counter);
void	ft_put_hex_or_ptr(unsigned long hex, char uppercase,
			unsigned int *counter, bool is_ptr);

void	flags(const char *str_char, va_list args, unsigned int *counter);
int		ft_printf(const char *str, ...);

#endif