/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:26:11 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/21 15:21:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	wait_philo(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (philo[i].id != -1)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

t_philosopher	*init_philo(t_data *data)
{
	t_philosopher	*philo;
	int				nbr;

	nbr = 0;
	if (data->philo_nbr > 200)
		return (NULL);
	philo = malloc(sizeof(t_philosopher) * (data->philo_nbr + 1));
	while (nbr < data->philo_nbr)
	{
		philo[nbr].data = data;
		philo[nbr].id = nbr + 1;
		pthread_create(&philo[nbr].thread_id, NULL, routine,
			(void *)&philo[nbr]);
		nbr++;
	}
	philo[nbr].id = -1;
	return (philo);
}

void	init_forks(t_data *data)
{
	int	i;
	int	nbr;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * (data->philo_nbr + 1));
	while (i < data->philo_nbr)
	{
		nbr = i + 1;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		if (nbr - 1 <= 0)
			data->forks[i].left_philo = data->philo_nbr;
		else
			data->forks[i].left_philo = nbr - 1;
		data->forks[i].right_philo = nbr;
		i++;
	}
}

int	init_times(char *argv[], t_data *data)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	if (data->time_to_sleep < 0 || data->time_to_eat < 0
		|| data->time_to_die < 0)
		return (0);
	return (1);
}

int	init(t_data *data, char *argv[])
{
	data->philo_nbr = ft_atoi(argv[1]);
	if (init_times(argv, data) == 0)
		return (1);
	init_forks(data);
	gettimeofday(&data->start, NULL);
	data->philo = init_philo(data);
	if (data->philo == NULL)
		return (1);
	wait_philo(data->philo);
	printf("%d ms ; Eat : %d ; Sleep : %d ; Die : %d)\n",
		get_current_operation_time(*data), data->time_to_eat,
		data->time_to_sleep, data->time_to_die);
	return (0);
}
