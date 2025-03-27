/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:53:56 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/27 01:23:18 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void handle_signal(int sig, siginfo_t *info, void *context)
{
    static unsigned char c = 0;
    static int bit_count = 0;
    static int current_pid = 0;

    (void)context;
    if (current_pid == 0)
        current_pid = info->si_pid;
    if (current_pid != info->si_pid) 
    {
        c = 0;
        bit_count = 0;
        current_pid = info->si_pid;
    }
    c |= (sig == SIGUSR2) << bit_count;
    bit_count++;
    if (bit_count == 8) 
    {
        if (c == 0) 
        {
            write(1, "\n", 1);
            current_pid = 0;
        } 
        else 
            write(1, &c, 1);
        c = 0;
        bit_count = 0;
    }
    kill(info->si_pid, SIGUSR1);
}

int main()
{
    struct sigaction sa;
    
    ft_printf("Server PID: %d\n", getpid());
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
    return 0;
}
