/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:27:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/17 12:13:27 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philosopher	t_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				left_philo;
	int				right_philo;
}		t_fork;

typedef struct s_data {
	struct s_philosopher	*philosopher;
	struct timeval			timeval;
	t_fork					*forks;
	int						nbr_iter;
	int						err;
}		t_data;

typedef struct s_philosopher
{
	t_data		*data;
	pthread_t	thread;
	int			id;
}		t_philosopher;

void	*routine(void *philosopher)
{
	t_philosopher	*current_philosopher;
	int				is_locked;
	int				i;
	unsigned int	wait_time;

	current_philosopher = philosopher;
	i = 0;
	wait_time = 100;
	while (i != current_philosopher->data->nbr_iter)
	{
		printf("Attente du philosopher %d\n", current_philosopher->id);
		pthread_mutex_lock(&current_philosopher->data->mutex);
		printf("Le philosopher avec l'ID %d a attrapé la fourchette\n",
			current_philosopher->id);
		pthread_mutex_unlock(&current_philosopher->data->mutex);
		usleep(wait_time);
		i++;
	}
	return ((void *)1);
}

int	main(void)
{
	t_philosopher				*philosophers;
	t_data						data;
	int							return_value;

	philosophers = malloc(sizeof(t_philosopher) * (2 + 1));
	data.nbr_iter = 5;
	philosophers[0].data = &data;
	philosophers[0].id = 0;
	philosophers[1].data = &data;
	philosophers[1].id = 1;
	pthread_create(&philosophers[0].thread, NULL, routine,
		(void *)philosophers);
	philosophers++;
	pthread_create(&philosophers[1].thread, NULL, routine,
		(void *)philosophers);
	pthread_mutex_init(&data.mutex, NULL);
	pthread_join(philosophers[0].thread, (void *)&return_value);
	pthread_join(philosophers[1].thread, (void *)&return_value);
	printf("\nFin\n");
	return (1);
}
