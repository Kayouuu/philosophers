/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:29:03 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/09 10:37:36 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	action_eat3(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->forks[1]].mutex);
	print_take(data, get_current_operation_time(*data), philo->id, philo);
	philo->time_wo_eating = get_time(*data, philo->eating_time);
	dying(*philo, data);
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
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->forks[philo->forks[0]].mutex);
	print_take(data, get_current_operation_time(*data), philo->id, philo);
	philo->time_wo_eating = get_time(*data, philo->eating_time);
	if (data->philo_nbr == 1)
		while (dying(*philo, data) == 0)
			philo->time_wo_eating = get_time(*data, philo->eating_time);
	else
		dying(*philo, data);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

int	action_eat(t_philo *philo, t_data *data)
{
	if (philo->time_wo_eating == -1)
	{
		philo->eating_time = get_current_operation_time(*data);
	}
	else
		philo->eating_time = get_current_operation_time(*data)
			- (data->time_to_sleep / 1000) - (data->time_to_eat / 1000);
	philo->time_wo_eating = get_time(*data, philo->eating_time);
	dying(*philo, data);
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (0);
	}
	pthread_mutex_unlock(&data->dead);
	if (action_eat2(philo, data) == 1)
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
