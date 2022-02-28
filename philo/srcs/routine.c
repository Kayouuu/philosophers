/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:51:16 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/28 09:52:57 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	is_forks_locked(t_philosopher philosopher, t_data data)
{
	if (data.forks[philosopher.forks[0]].is_locked == 0
		&& data.forks[philosopher.forks[1]].is_locked == 0)
		return (0);
	else
		return (1);
}

int	dying(t_philosopher philosopher, t_data *data)
{
	if (philosopher.time_wo_eating
		>= (data->time_to_die / 1000))
	{
		if (data->is_dead == 1)
			return (1);
		data->is_dead = 1;
		pthread_mutex_lock(&data->can_write);
		if (data->can_write_death == 0)
			return (1);
		data->can_write_death = 0;
		printf("%d %d died\n",
			get_current_operation_time(*data), philosopher.id);
		return (1);
	}
	return (0);
}

int	action_eat(t_philosopher *philosopher, t_data *data)
{
	if (philosopher->time_wo_eating == -1)
		philosopher->eating_time = get_current_operation_time(*data);
	else
		philosopher->eating_time = get_current_operation_time(*data)
			- (data->time_to_sleep / 1000) - (data->time_to_eat / 1000);
	while (is_forks_locked(*philosopher, *data) == 1
		&& dying(*philosopher, data) == 0
		&& data->is_dead == 0)
		philosopher->time_wo_eating = get_time(*data,
				philosopher->eating_time);
	// printf("[%d] %d - %d\n", philosopher->id, philosopher->time_wo_eating, philosopher->eating_time);
	if (data->is_dead == 1)
		return (0);
	data->forks[philosopher->forks[0]].is_locked = 1;
	data->forks[philosopher->forks[1]].is_locked = 1;
	pthread_mutex_lock(&data->forks[philosopher->forks[0]].mutex);
	pthread_mutex_lock(&data->forks[philosopher->forks[1]].mutex);
	print_take(data, get_current_operation_time(*data), philosopher->id);
	print_take(data, get_current_operation_time(*data), philosopher->id);
	if (data->is_dead == 1)
		return (0);
	print_eat(data, get_current_operation_time(*data), philosopher->id);
	msleep(data->time_to_eat);
	if (data->is_dead == 1)
		return (0);
	return (1);
}

int	action_sleep(t_philosopher *philosopher, t_data *data)
{
	print_sleep(data, get_current_operation_time(*data), philosopher->id);
	pthread_mutex_unlock(&data->forks[philosopher->forks[0]].mutex);
	pthread_mutex_unlock(&data->forks[philosopher->forks[1]].mutex);
	data->forks[philosopher->forks[0]].is_locked = 0;
	data->forks[philosopher->forks[1]].is_locked = 0;
	// philosopher->eating_time = get_current_operation_time(*data);
	msleep(data->time_to_sleep);
	if (data->is_dead == 1)
		return (0);
	return (1);
}

void	*routine(void *current_philosopher)
{
	t_philosopher	*philosopher;
	t_data			*data;
	int				i;

	philosopher = current_philosopher;
	data = philosopher->data;
	if (philosopher->id == data->philo_nbr - 1)
		data->is_threads_created = 1;
	while (data->is_threads_created == 0)
		continue ;
	get_forks(&philosopher);
	philosopher->eating_time = get_current_operation_time(*data);
	philosopher->time_wo_eating = -1;
	gettimeofday(&data->start, NULL);
	i = 0;
	while (data->is_dead == 0)
	{
		// if (philosopher->id % 2 == 0)
		// 	usleep(10);
		action_eat(philosopher, data);
		action_sleep(philosopher, data);
		print_thinking(data,
			get_current_operation_time(*data), philosopher->id);
		i++;
	}
	return ((void *) 1);
}
