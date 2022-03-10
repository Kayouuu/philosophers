/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:51:16 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/10 09:49:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	dying(t_philo philosopher, t_data *data)
{
	if (philosopher.time_wo_eating
		>= (int)(data->time_to_die / 1000))
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			return (1);
		}
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_lock(&data->can_write);
		if (data->can_write_death == 0)
		{
			pthread_mutex_unlock(&data->can_write);
			return (1);
		}
		data->can_write_death = 0;
		printf("%d %d died\n",
			get_current_operation_time(*data), philosopher.id);
		pthread_mutex_unlock(&data->can_write);
		return (1);
	}
	return (0);
}

static int	init_routine(t_philo *philosopher, t_data *data)
{
	if (philosopher->id == data->philo_nbr)
	{
		gettimeofday(&data->start, NULL);
		pthread_mutex_lock(&data->are_threads_created);
		data->is_threads_created = 1;
		pthread_mutex_unlock(&data->are_threads_created);
	}
	while (data->philo_nbr != 1)
	{
		pthread_mutex_lock(&data->are_threads_created);
		if (data->is_threads_created == 1 || data->philo_nbr == 1)
			break ;
		pthread_mutex_unlock(&data->are_threads_created);
	}
	pthread_mutex_unlock(&data->are_threads_created);
	philosopher->iteration = data->iteration;
	get_forks(&philosopher);
	philosopher->time_wo_eating = -1;
	if (data->philo_nbr == 1)
		gettimeofday(&data->start, NULL);
	if (philosopher->id % 2)
		msleep(100 * data->philo_nbr);
	return (1);
}

void	*routine(void *current_philo)
{
	t_philo			*philo;
	t_data			*data;
	int				i;

	philo = current_philo;
	data = philo->data;
	if (init_routine(philo, data) == 0)
		return (0);
	i = 0;
	while (i++ != philo->iteration)
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			break ;
		}
		pthread_mutex_unlock(&data->dead);
		if (action_eat(philo, data) == 0 || action_sleep(philo, data) == 0)
			return ((void *)(write(2, "Error\n", 7) * 0));
		print_thinking(data, get_current_operation_time(*data), philo->id);
	}
	return ((void *) 1);
}
