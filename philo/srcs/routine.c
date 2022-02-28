/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:51:16 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/28 15:07:39 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	is_forks_locked(t_philosopher philosopher, t_data data)
{
	if (data.forks[philosopher.forks[0]].is_locked == 0
		&& data.forks[philosopher.forks[1]].is_locked == 0
		&& data.philo_nbr != 1)
		return (0);
	else
		return (1);
}

int	dying(t_philosopher philosopher, t_data *data)
{
	if (philosopher.time_wo_eating
		>= (int)(data->time_to_die / 1000))
	{
		if (data->is_dead == 1)
			return (1);
		data->is_dead = 1;
		pthread_mutex_lock(&data->can_write);
		if (data->can_write_death == 0)
			return (1);
		data->can_write_death = 0;
		pthread_mutex_unlock(&data->can_write);
		printf("%d %d died\n",
			get_current_operation_time(*data), philosopher.id);
		return (1);
	}
	return (0);
}

static void	init_routine(t_philosopher *philosopher, t_data *data)
{
	if (philosopher->id == data->philo_nbr - 1)
		data->is_threads_created = 1;
	while (data->is_threads_created == 0 && data->philo_nbr != 1)
		continue ;
	philosopher->iteration = data->iteration;
	get_forks(&philosopher);
	philosopher->time_wo_eating = -1;
	gettimeofday(&data->start, NULL);
}

void	*routine(void *current_philosopher)
{
	t_philosopher	*philosopher;
	t_data			*data;
	int				i;

	philosopher = current_philosopher;
	data = philosopher->data;
	init_routine(philosopher, data);
	i = 0;
	while (data->is_dead == 0 && i++ != philosopher->iteration)
	{
		if (action_eat(philosopher, data) == 0
			|| action_sleep(philosopher, data) == 0)
		{
			write(2, "Error\n", 7);
			return ((void *) 0);
		}
		print_thinking(data,
			get_current_operation_time(*data), philosopher->id);
		usleep(100);
	}
	return ((void *) 1);
}
