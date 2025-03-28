/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 07:59:12 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/28 17:28:26 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static int g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_bit(int pid, int bit)
{
	int	timeout;

	timeout = 1000;
	g_ack_received = 0;
	if (bit)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
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

static int	init_client(int argc, char **argv, struct sigaction *sa, int *pid)
{
	char	*msg;

	if (argc != 3)
		return (write(2, RED "Error: ./client_bonus <PID> <message>\n" RESET,
				42), 1);
	if (!is_valid_pid(argv[1]))
		return (write(2, RED "Invalid PID Format\n" RESET,
				ft_strlen(RED "Invalid PID Format\n" RESET)), 1);
	sa->sa_handler = ack_handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
	*pid = ft_atoi(argv[1]);
	msg = argv[2];
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (init_client(argc, argv, &sa, &pid))
		return (1);
	while (*argv[2])
		send_char(pid, *argv[2]++);
	send_char(pid, '\0');
	while (!g_ack_received)
		usleep(1);
	ft_printf(CYAN "Acknowledgment received from server\n" RESET);
	return (0);
}
