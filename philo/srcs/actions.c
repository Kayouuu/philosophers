/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:29:03 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/11 16:06:30 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	msleep2(int time, struct timeval start)
{
	int				start_time;
	int				current_time;
	struct timeval	current;

	start_time = (start.tv_sec * 1000 + start.tv_usec / 1000);
	usleep(time * 0.95);
	gettimeofday(&current, NULL);
	current_time = ((current.tv_sec * 1000 + current.tv_usec / 1000)
			- start_time);
	while (current_time * 1000 < time)
	{
		usleep(1);
		gettimeofday(&current, NULL);
		current_time = ((current.tv_sec * 1000 + current.tv_usec / 1000)
				- start_time);
	}
}

static int	action_eat3(t_philo *philo, t_data *data)
{
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
	msleep2(data->time_to_eat, philo->start);
	pthread_mutex_unlock(&data->forks[philo->forks[0]].mutex);
	pthread_mutex_unlock(&data->forks[philo->forks[1]].mutex);
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
	if (data->philo_nbr == 1)
	{
		print_take(data, get_current_operation_time(*data), philo->id, philo);
		while (dying(*philo, data) == 0)
			philo->time_wo_eating = get_time(*data, philo->eating_time);
		return (0);
	}
	pthread_mutex_lock(&data->forks[philo->forks[1]].mutex);
	gettimeofday(&philo->start, NULL);
	print_take(data, get_current_operation_time(*data), philo->id, philo);
	print_take(data, get_current_operation_time(*data), philo->id, philo);
	philo->time_wo_eating = get_time(*data, philo->eating_time);
	dying(*philo, data);
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
	philo->time_wo_eating = philo->eating_time;
	if (action_eat2(philo, data) == 1)
		return (1);
	return (action_eat3(philo, data));
}

int	action_sleep(t_philo *philo, t_data *data)
{
	print_sleep(data, get_current_operation_time(*data), philo->id, philo);
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
