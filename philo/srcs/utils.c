/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:01:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/21 12:30:43 by psaulnie         ###   ########.fr       */
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
		if ((nb * 10 + (str[n] - '0')) / 10 != nb)
			return (-1);
		nb *= 10;
		nb += str[n++] - 48;
	}
	if (negative == -1)
		return (-1);
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

int	get_forks(t_philosopher **philosopher)
{
	int	i;
	int	id;

	i = 0;
	id = (*philosopher)->id;
	(*philosopher)->forks[0] = -1;
	(*philosopher)->forks[1] = -1;
	while (i < (*philosopher)->data->philo_nbr)
	{
		if ((*philosopher)->data->forks[i].left_philo == id)
			(*philosopher)->forks[0] = i;
		if ((*philosopher)->data->forks[i].right_philo == id)
			(*philosopher)->forks[1] = i;
		i++;
	}
	if ((*philosopher)->forks[0] == -1)
		(*philosopher)->forks[0] = (*philosopher)->forks[1] - 2;
	if ((*philosopher)->forks[1] == -1)
		(*philosopher)->forks[1] = (*philosopher)->forks[0] + 2;
	return (1);
}
