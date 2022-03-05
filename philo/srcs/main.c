/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:51:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/05 11:54:55 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_unlock(&data->are_threads_created);
	pthread_mutex_unlock(&data->can_write);
	pthread_mutex_unlock(&data->is_locked);
	pthread_mutex_destroy(&data->are_threads_created);
	pthread_mutex_destroy(&data->can_write);
	pthread_mutex_destroy(&data->is_locked);
	i = 0;
	while (data->forks[i].left_philo != -1)
	{
		pthread_mutex_unlock(&data->forks[i].mutex);
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	if (init(&data, argc, argv) == 1)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	return (1);
}
