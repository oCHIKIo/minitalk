/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:33:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/29 00:06:55 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	validate_args(int argc, char **argv)
{
	if (argc != 3)
	{
		write(2, RED "Error: ./client <PID> <message>\n" RESET,
			ft_strlen(RED "Error: ./client <PID> <message>\n" RESET));
		return (0);
	}
	if (!is_valid_pid(argv[1]))
	{
		write(2, RED "Invalid PID Format\n" RESET,
			ft_strlen(RED "Invalid PID Format\n" RESET));
		return (0);
	}
	return (1);
}
