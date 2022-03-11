/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:00:31 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/10 15:33:49 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	print_take(t_data *data, int operation_time, int id, t_philo *philo)
{
	pthread_mutex_lock(&data->can_write);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1 || data->can_write_death == 0)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
		pthread_mutex_unlock(&data->can_write);
		return (0);
	}
	pthread_mutex_unlock(&data->dead);
	printf("%d %d has taken a fork\n", operation_time, id);
	pthread_mutex_unlock(&data->can_write);
	return (1);
}

int	print_eat(t_data *data, int operation_time, int id, t_philo *philo)
{
	pthread_mutex_lock(&data->can_write);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1 || data->can_write_death == 0)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
		pthread_mutex_unlock(&data->can_write);
		return (0);
	}
	pthread_mutex_unlock(&data->dead);
	printf("%d %d is eating\n", operation_time, id);
	pthread_mutex_unlock(&data->can_write);
	return (1);
}

int	print_sleep(t_data *data, int operation_time, int id, t_philo *philo)
{
	pthread_mutex_lock(&data->can_write);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1 || data->can_write_death == 0)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
		pthread_mutex_unlock(&data->can_write);
		return (0);
	}
	pthread_mutex_unlock(&data->dead);
	printf("%d %d is sleeping\n", operation_time, id);
	pthread_mutex_unlock(&data->can_write);
	return (1);
}

int	print_thinking(t_data *data, int operation_time, int id)
{
	pthread_mutex_lock(&data->can_write);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1 || data->can_write_death == 0)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->can_write);
		return (0);
	}
	pthread_mutex_unlock(&data->dead);
	printf("%d %d is thinking\n", operation_time, id);
	pthread_mutex_unlock(&data->can_write);
	return (1);
}
