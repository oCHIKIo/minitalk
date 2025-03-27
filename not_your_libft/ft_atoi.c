/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:18:03 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/27 01:25:05 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	t_nbr	nbr;

	nbr.sign = 1;
	nbr.res = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			nbr.sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr.res = nbr.res * 10 + (*str - '0');
		str++;
	}
	return (nbr.sign * nbr.res);
}
