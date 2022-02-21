/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:26:11 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/18 13:26:19 by psaulnie         ###   ########.fr       */
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

t_philosopher	*init_philo(char *number_of_philo, t_data *data)
{
	t_philosopher	*philo;
	int				nbr;

	nbr = 0;
	data->philo_nbr = ft_atoi(number_of_philo);
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
		{
			data->forks[i].left_philo = data->philo_nbr;
			data->forks[i].right_philo = 1;
		}
		else
		{
			data->forks[i].left_philo = i - 1;
			data->forks[i].right_philo = i + 1;
		}
		i++;
	}
}

int	init(t_data *data, char *argv[])
{
	data->philo = init_philo(argv[1], data);
	init_forks(data);
	if (data->philo == NULL)
		return (1);
	gettimeofday(&data->start, NULL);
	wait_philo(data->philo);
	printf("%d ms\n", get_current_operation_time(*data));
	return (0);
}
