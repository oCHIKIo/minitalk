/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:18:03 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/28 08:30:00 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_atoi(const char *str)
{
    long temp;

    temp = 0;
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    while (*str >= '0' && *str <= '9')
    {
        temp = temp * 10 + (*str - '0');
        if (temp > 2147483647)
        {
            write(2, RED "Overflow: Number out of range" RESET "\n",
                ft_strlen(RED "Overflow: Number out of range" RESET "\n"));
            return (2147483647);
        }
        str++;
    }
    return ((int)temp);
}
