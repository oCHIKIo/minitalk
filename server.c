/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:53:56 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/28 18:24:28 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_variables(unsigned char *c, int *bit_count, int *current_pid,
		int new_pid)
{
	*c = 0;
	*bit_count = 0;
	*current_pid = new_pid;
}

static void	process_character(unsigned char *c, int *bit_count, int client_pid)
{
	if (*c == 0)
	{
		write(1, "\n", 1);
		reset_variables(c, bit_count, &client_pid, 0);
	}
	else
		write(1, c, 1);
	*c = 0;
	*bit_count = 0;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;
	static int				current_pid = 0;

	(void)context;
	if (current_pid == 0)
		current_pid = info->si_pid;
	if (current_pid != info->si_pid)
		reset_variables(&c, &bit_count, &current_pid, info->si_pid);
	c |= (sig == SIGUSR2) << bit_count;
	bit_count++;
	if (bit_count == 8)
		process_character(&c, &bit_count, current_pid);
	kill(info->si_pid, SIGUSR1);
}
int main(void) 
{
    struct sigaction sa;

    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1) 
    {
        write(2, RED "Error: sigaction for SIGUSR1 failed\n" RESET, 
             ft_strlen(RED "Error: sigaction for SIGUSR1 failed\n" RESET));
        exit(1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1) 
    {
        write(2, RED "Error: sigaction for SIGUSR2 failed\n" RESET, 
             ft_strlen(RED "Error: sigaction for SIGUSR2 failed\n" RESET));
        exit(1);
    }
    ft_printf(YELLOW "Get Your Server PID: %d\n" RESET, getpid());
    while (1)
        pause();
    return (0);
}
