/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:26:11 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/28 09:31:22 by psaulnie         ###   ########.fr       */
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

	i = 0;
	data->forks = malloc(sizeof(t_fork) * (data->philo_nbr + 1));
	while (i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		if (i == 0)
			data->forks[i].left_philo = data->philo_nbr;
		else
			data->forks[i].left_philo = i;
		if (i + 1 == data->philo_nbr)
			data->forks[i].right_philo = 0;
		else
			data->forks[i].right_philo = i + 1;
		data->forks[i].is_locked = 0;
		i++;
	}
}

int	init_times(int argc, char *argv[], t_data *data)
{
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->iteration = ft_atoi(argv[5]);
	else
		data->iteration = -1;
	data->is_dead = 0;
	data->can_write_death = 1;
	if (data->time_to_sleep < 0 || data->time_to_eat < 0
		|| data->time_to_die < 0)
		return (0);
	return (1);
}

int	init(t_data *data, int argc, char *argv[])
{
	data->philo_nbr = ft_atoi(argv[1]);
	if (init_times(argc, argv, data) == 0)
		return (1);
	init_forks(data);
	data->philo = init_philo(data);
	if (data->philo == NULL)
		return (1);
	wait_philo(data->philo);
	return (0);
}
