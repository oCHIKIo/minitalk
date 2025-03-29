/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:53:47 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/29 00:20:01 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_bit(int pid, int bit)
{
	int	timeout;

	g_ack_received = 0;
	if (bit)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			write(2, "Error: kill failed\n", 19);
			exit(1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write(2, "Error: kill failed\n", 19);
			exit(1);
		}
	}
	timeout = 1000;
	while (!g_ack_received && timeout-- > 0)
		usleep(1);
}

static void	send_char(int pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
		send_bit(pid, (c >> i) & 1);
}

static int	init_client(int argc, char **argv, int *pid, char **msg)
{
	struct sigaction	sa;

	if (!validate_args(argc, argv))
		return (0);
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		write(2, RED "Error: sigemptyset failed\n" RESET,
			ft_strlen(RED "Error: sigemptyset failed\n" RESET));
		exit(1);
	}
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(1);
	}
	*pid = ft_atoi(argv[1]);
	*msg = argv[2];
	return (1);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;

	if (!init_client(argc, argv, &pid, &msg))
		return (1);
	while (*msg)
		send_char(pid, *msg++);
	send_char(pid, '\0');
	return (0);
}
