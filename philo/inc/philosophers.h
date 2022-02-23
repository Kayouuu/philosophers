/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:43:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/23 16:50:12 by psaulnie         ###   ########.fr       */
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
	pthread_mutex_t			can_write;
	struct s_philosopher	*philo;
	struct timeval			start;
	int						philo_nbr;
	int						time_to_eat;
	int						time_to_sleep;
	int						time_to_die;
	int						is_dead;
	int						can_write_death;
	int						is_threads_created;
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

/*	LOGS.C	*/

int		print_take(t_data *data, int operation_time, int id);
int		print_eat(t_data *data, int operation_time, int id);
int		print_sleep(t_data *data, int operation_time, int id);
int		print_thinking(t_data *data, int operation_time, int id);

/*	ROUTINE.C	*/

void	*routine(void *current_philosopher);

/*	UTILS.C	*/

int		ft_atoi(const char *str);
int		get_current_operation_time(t_data data);
int		get_time(t_data data, int eating_time);
int		get_forks(t_philosopher **philosopher);
int		msleep(int time);

#endif
