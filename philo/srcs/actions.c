/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:29:03 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/28 14:48:49 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	action_eat2(t_philosopher *philosopher, t_data *data)
{
	if (pthread_mutex_lock(&data->forks[philosopher->forks[0]].mutex) != 0)
		return (0);
	if (pthread_mutex_lock(&data->forks[philosopher->forks[1]].mutex) != 0)
		return (0);
	print_take(data, get_current_operation_time(*data), philosopher->id);
	print_take(data, get_current_operation_time(*data), philosopher->id);
	if (data->is_dead == 1)
		return (1);
	print_eat(data, get_current_operation_time(*data), philosopher->id);
	msleep(data->time_to_eat);
	if (data->is_dead == 1)
		return (1);
	return (1);
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
	if (data->is_dead == 1)
		return (1);
	data->forks[philosopher->forks[0]].is_locked = 1;
	data->forks[philosopher->forks[1]].is_locked = 1;
	action_eat2(philosopher, data);
	return (1);
}

int	action_sleep(t_philosopher *philosopher, t_data *data)
{
	print_sleep(data, get_current_operation_time(*data), philosopher->id);
	if (pthread_mutex_unlock(&data->forks[philosopher->forks[0]].mutex) != 0)
		return (0);
	if (pthread_mutex_unlock(&data->forks[philosopher->forks[1]].mutex) != 0)
		return (0);
	data->forks[philosopher->forks[0]].is_locked = 0;
	data->forks[philosopher->forks[1]].is_locked = 0;
	msleep(data->time_to_sleep);
	if (data->is_dead == 1)
		return (1);
	return (1);
}
