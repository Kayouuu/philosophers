/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:26:11 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/05 11:47:40 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	wait_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo[i].id != -1)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int				nbr;

	nbr = 0;
	if (data->philo_nbr > 200)
		return (NULL);
	philo = malloc(sizeof(t_philo) * (data->philo_nbr + 1));
	if (!philo)
		return (NULL);
	while (nbr < data->philo_nbr)
	{
		philo[nbr].data = data;
		philo[nbr].id = nbr + 1;
		if (pthread_create(&philo[nbr].thread_id, NULL, routine,
				(void *)&philo[nbr]) != 0)
			return (NULL);
		nbr++;
	}
	philo[nbr].id = -1;
	return (philo);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * (data->philo_nbr + 1));
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
			return (0);
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
	data->forks[i].left_philo = -1;
	if (pthread_mutex_init(&data->can_write, NULL) != 0
		|| pthread_mutex_init(&data->are_threads_created, NULL) != 0
		|| pthread_mutex_init(&data->is_locked, NULL) != 0
		|| pthread_mutex_init(&data->dead, NULL) != 0)
		return (0);
	return (1);
}

int	init_times(int argc, char *argv[], t_data *data)
{
	int	tmp;
	int	tmp2;
	int	tmp3;

	tmp = ft_atoi(argv[2]);
	tmp2 = ft_atoi(argv[3]);
	tmp3 = ft_atoi(argv[4]);
	if (argc == 6)
		data->iteration = ft_atoi(argv[5]);
	else
		data->iteration = -1;
	data->is_dead = 0;
	data->can_write_death = 1;
	if (tmp < 0 || tmp2 < 0
		|| tmp3 < 0 || (data->iteration < 0 && argc == 6))
		return (0);
	data->time_to_die = tmp * 1000;
	data->time_to_eat = tmp2 * 1000;
	data->time_to_sleep = tmp3 * 1000;
	return (1);
}

int	init(t_data *data, int argc, char *argv[])
{
	data->philo_nbr = ft_atoi(argv[1]);
	if (init_times(argc, argv, data) == 0)
	{
		printf("c\n");
		return (1);
	}
	if (init_forks(data) == 0)
	{
		printf("b\n");
		return (1);
	}
	data->philo = init_philo(data);
	if (data->philo == NULL)
	{
		printf("a\n");
		return (1);
	}
	if (wait_philo(data->philo) == 0)
		return (1);
	clean(data);
	return (0);
}
