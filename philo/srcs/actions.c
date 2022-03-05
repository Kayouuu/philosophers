/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:29:03 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/05 11:55:35 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	action_eat2(t_philo *philosopher, t_data *data)
{
	if (pthread_mutex_lock(&data->forks[philosopher->forks[0]].mutex) != 0)
		return (0);
	print_take(data, get_current_operation_time(*data), philosopher->id, philosopher);
	if (pthread_mutex_lock(&data->forks[philosopher->forks[1]].mutex) != 0)
		return (0);
	print_take(data, get_current_operation_time(*data), philosopher->id, philosopher);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philosopher->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philosopher->forks[1]].mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	print_eat(data, get_current_operation_time(*data), philosopher->id, philosopher);
	msleep(data->time_to_eat);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philosopher->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philosopher->forks[1]].mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (1);
}

int	action_eat(t_philo *philosopher, t_data *data)
{
	if (philosopher->time_wo_eating == -1)
		philosopher->eating_time = get_current_operation_time(*data);
	else
		philosopher->eating_time = get_current_operation_time(*data)
			- (data->time_to_sleep / 1000) - (data->time_to_eat / 1000);
	while (is_forks_locked(*philosopher, data) == 1
		&& dying(*philosopher, data) == 0)
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		philosopher->time_wo_eating = get_time(*data,
				philosopher->eating_time);
	}
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->is_locked);
	data->forks[philosopher->forks[0]].is_locked = 1;
	data->forks[philosopher->forks[1]].is_locked = 1;
	pthread_mutex_unlock(&data->is_locked);
	return (action_eat2(philosopher, data));
}

int	action_sleep(t_philo *philosopher, t_data *data)
{
	print_sleep(data, get_current_operation_time(*data), philosopher->id);
	if (pthread_mutex_unlock(&data->forks[philosopher->forks[0]].mutex) != 0)
		return (0);
	if (pthread_mutex_unlock(&data->forks[philosopher->forks[1]].mutex) != 0)
		return (0);
	pthread_mutex_lock(&data->is_locked);
	data->forks[philosopher->forks[0]].is_locked = 0;
	data->forks[philosopher->forks[1]].is_locked = 0;
	pthread_mutex_unlock(&data->is_locked);
	msleep(data->time_to_sleep);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (1);
}
