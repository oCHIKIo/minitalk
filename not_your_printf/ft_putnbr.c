/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:15:07 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/27 21:15:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	number;

	number = 0;
	if (n == INT_MIN)
	{
		number += write(1, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		number += write(1, "-", 1);
		n = -n;
	}
	if (n == 0)
		return (write(1, "0", 1));
	if (n > 9)
		number += ft_putnbr(n / 10);
	number += ft_putchar(n % 10 + '0');
	return (number);
}
