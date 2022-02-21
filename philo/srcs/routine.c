/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:51:16 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/21 15:21:35 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *current_philosopher)
{
	t_philosopher	*philosopher;
	t_data			*data;
	int				next_philo;

	philosopher = current_philosopher;
	data = philosopher->data;
	get_forks(&philosopher);
	philosopher->is_eating = 0;
	next_philo = philosopher->id - 1;
	if (next_philo <= 0)
		next_philo = philosopher->data->philo_nbr;
	while (data->is_dead == 0)
	{
		while (philosopher->data->philo[next_philo].is_eating)
			continue ;
		pthread_mutex_lock(&data->forks[philosopher->forks[0]].mutex);
		printf("[%d ms] Philosopher %d has taken a fork\n",
			get_current_operation_time(*data), philosopher->id);
		pthread_mutex_lock(&data->forks[philosopher->forks[1]].mutex);
		printf("[%d ms] Philosopher %d has taken a fork\n",
			get_current_operation_time(*data), philosopher->id);
		printf("[%d ms] Philosopher %d is eating\n",
			get_current_operation_time(*data), philosopher->id);
		philosopher->is_eating = 1;
		usleep(data->time_to_eat * 1000);
		philosopher->is_eating = 0;
		printf("[%d ms] Philosopher %d is sleeping\n",
			get_current_operation_time(*data), philosopher->id);
		pthread_mutex_unlock(&data->forks[philosopher->forks[0]].mutex);
		pthread_mutex_unlock(&data->forks[philosopher->forks[1]].mutex);
		usleep(data->time_to_sleep * 1000);
		printf("[%d ms] Philosopher %d is thinking\n",
			get_current_operation_time(*data), philosopher->id);
	}
	return ((void *) 1);
}
