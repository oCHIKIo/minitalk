/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:16:30 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/27 21:16:30 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_num(unsigned int n)
{
	int	number;

	number = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n > 9)
		number += ft_unsigned_num(n / 10);
	number += ft_putchar(n % 10 + '0');
	return (number);
}
