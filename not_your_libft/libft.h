/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:18:50 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/28 08:30:38 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minitalk.h"

typedef struct s_nbr
{
	int	x;
}		t_nbr;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		is_valid_pid(const char *str);

#endif
