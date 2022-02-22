/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:43:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/22 15:52:54 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*	INCLUDES	*/

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

/*	STRUCTS	*/

typedef struct s_philosopher	t_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				is_locked;
	int				left_philo;
	int				right_philo;
}		t_fork;

typedef struct s_data {
	t_fork					*forks;
	struct s_philosopher	*philo;
	struct timeval			start;
	int						philo_nbr;
	int						time_to_eat;
	int						time_to_sleep;
	int						time_to_die;
	int						is_dead;
}		t_data;

typedef struct s_philosopher
{
	t_data			*data;
	pthread_t		thread_id;
	int				forks[2];
	int				id;
	int				eating_time;
	int				time_wo_eating;
}		t_philosopher;

/*	INIT.C	*/

void	wait_philo(t_philosopher *philo);
int		init(t_data *data, char *argv[]);

/*	ROUTINE.C	*/

void	*routine(void *current_philosopher);

/*	UTILS.C	*/

int		ft_atoi(const char *str);
int		get_current_operation_time(t_data data);
int		get_time(t_data data, int eating_time);
int		get_forks(t_philosopher **philosopher);

#endif
