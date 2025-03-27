/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:53:47 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/27 02:49:13 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t g_ack_received = 0;

static int is_valid_pid(char const *str)
{
    if(!str || !*str)
        return 0;
    while(*str)
    {
        if(!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}
static void ack_handler(int sig)
{
    (void)sig;
    g_ack_received = 1;
}

static void send_bit(int pid, int bit) 
{
    g_ack_received = 0;
    
    if (bit)
        kill(pid, SIGUSR2);
    else
        kill(pid, SIGUSR1);
    int timeout = 1000;
    while (!g_ack_received && timeout-- > 0)
        usleep(1);
}

static void send_char(int pid, char c) 
{
    int i;
    
    i = -1;
    while(++i < 8)
        send_bit(pid, (c >> i) & 1);
}

int main(int argc, char **argv)
{
    if (argc != 3) 
    {
        write(2, RED "Error: ./client <PID> <message>\n" RESET,
            ft_strlen(RED "Error: ./client <PID> <message>\n" RESET));
        return 1;
    }
    if (!is_valid_pid(argv[1]))
    {
        write(2, RED "Invalid PID Format\n" RESET, 
            ft_strlen(RED "Invalid PID Format\n" RESET));
        return 1;
    }
    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    int pid = ft_atoi(argv[1]);
    char *msg = argv[2];
    while (*msg)
        send_char(pid, *msg++);
    send_char(pid, '\0');
    return 0;
}
