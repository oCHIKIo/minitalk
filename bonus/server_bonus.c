/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 07:59:22 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/28 23:57:37 by bchiki           ###   ########.fr       */
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
		ft_printf(YELLOW "Message received! :)\n" RESET);
		if (kill(pid, SIGUSR1) == -1)
		{
			write(2, RED "Error: kill failed\n" RESET,
				ft_strlen(RED "Error: kill failed\n" RESET));
			exit(1);
		}
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
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		write(2, RED "Error: sigemptyset failed\n" RESET,
			ft_strlen(RED "Error: sigemptyset failed\n" RESET));
		exit(1);
	}
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
	{
		write(2, RED "Error: sigaction failed\n" RESET,
			ft_strlen(RED "Error: sigaction failed\n" RESET));
		exit(1);
	}
	ft_printf(YELLOW "Get Your Server PID: %d\n" RESET, getpid());
	while (1)
		pause();
	return (0);
}
