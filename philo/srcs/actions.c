/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:29:03 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/07 13:22:05 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	action_eat3(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->forks[0]].mutex);
	print_take(data, get_current_operation_time(*data), philo->id, philo);
	pthread_mutex_lock(&data->forks[philo->forks[1]].mutex);
	print_take(data, get_current_operation_time(*data), philo->id, philo);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	print_eat(data, get_current_operation_time(*data), philo->id, philo);
	msleep(data->time_to_eat);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (1);
}

static int	action_eat2(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (0);
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->is_locked);
	data->forks[philo->forks[0]].is_locked = 1;
	data->forks[philo->forks[1]].is_locked = 1;
	pthread_mutex_unlock(&data->is_locked);
	return (1);
}

int	action_eat(t_philo *philo, t_data *data)
{
	if (philo->time_wo_eating == -1)
		philo->eating_time = get_current_operation_time(*data);
	else
		philo->eating_time = get_current_operation_time(*data)
			- (data->time_to_sleep / 1000) - (data->time_to_eat / 1000);
	while (is_forks_locked(*philo, data) == 1
		&& dying(*philo, data) == 0)
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		philo->time_wo_eating = get_time(*data, philo->eating_time);
	}
	if (action_eat2(philo, data) == 0)
		return (1);
	return (action_eat3(philo, data));
}

int	action_sleep(t_philo *philo, t_data *data)
{
	print_sleep(data, get_current_operation_time(*data), philo->id, philo);
	pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
	pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->is_locked);
	data->forks[philo->forks[0]].is_locked = 0;
	data->forks[philo->forks[1]].is_locked = 0;
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
