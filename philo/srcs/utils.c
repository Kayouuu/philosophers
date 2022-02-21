/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:01:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/17 14:00:28 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(const char *str)
{
	int		n;
	long	nb;
	int		negative;

	n = 0;
	nb = 0;
	negative = 1;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\n' || str[n] == '\v'
		|| str[n] == '\f' || str[n] == '\r')
		n++;
	if (str[n] == '-')
		negative = -1;
	if (str[n] == '+' || str[n] == '-')
		n++;
	while (str[n] && !(str[n] < 48 || str[n] > 57))
	{
		if ((nb * 10 + (str[n] - '0')) / 10 != nb && negative == -1)
			return (0);
		else if ((nb * 10 + (str[n] - '0')) / 10 != nb)
			return (-1);
		nb *= 10;
		nb += str[n++] - 48;
	}
	return ((int)nb * negative);
}

int	get_current_operation_time(t_data data)
{
	struct timeval	current;
	int				time;

	gettimeofday(&current, NULL);
	time = ((current.tv_sec * 1000 + current.tv_usec / 1000)
			- (data.start.tv_sec * 1000 + data.start.tv_usec / 1000));
	return (time);
}
