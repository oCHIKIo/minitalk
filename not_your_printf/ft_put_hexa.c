/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:18:52 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/27 21:18:52 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hexa(unsigned long n, char format)
{
	char	*hexa;
	int		number;

	number = 0;
	if (format == 'x')
		hexa = "0123456789abcdef";
	else
		hexa = "0123456789ABCDEF";
	if (n >= 16)
		number += ft_put_hexa(n / 16, format);
	number += ft_putchar(hexa[n % 16]);
	return (number);
}
