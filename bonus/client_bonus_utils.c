/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:03 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/29 00:01:27 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	check_sigemptyset(struct sigaction *sa)
{
	if (sigemptyset(&sa->sa_mask) == -1)
	{
		write(2, RED "Error: sigemptyset failed\n" RESET,
			ft_strlen(RED "Error: sigemptyset failed\n" RESET));
		exit(1);
	}
	return (0);
}
