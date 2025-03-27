/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 07:59:22 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/27 08:30:54 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static void	reset_state(unsigned char *c, int *bit_count, int *current_pid,
		int new_pid)
{
	*c = 0;
	*bit_count = 0;
	*current_pid = new_pid;
}

static void	print_char(unsigned char c, int pid)
{
	if (c == 0)
	{
		write(1, "\n", 1);
		ft_printf(YELLOW "Message received!\n" RESET);
		kill(pid, SIGUSR1);
	}
	else
		write(1, &c, 1);
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;
	static int				current_pid = 0;

	(void)context;
	if (current_pid == 0 || current_pid != info->si_pid)
		reset_state(&c, &bit_count, &current_pid, info->si_pid);
	c |= (sig == SIGUSR2) << bit_count;
	bit_count++;
	if (bit_count == 8)
	{
		print_char(c, info->si_pid);
		c = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf(YELLOW "Server PID: %d\n" RESET, getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
