/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:18:50 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/27 02:28:34 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_nbr
{
    int x;
    int sign;
    int	res;    
}              t_nbr;

int	ft_isdigit(int c);
int ft_atoi(const char *str);
int ft_strlen(const char *str);

#endif
