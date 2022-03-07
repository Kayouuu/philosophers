/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:43:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/07 13:15:06 by psaulnie         ###   ########.fr       */
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

typedef struct s_philosopher	t_philo;

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
	pthread_mutex_t			is_locked;
	pthread_mutex_t			are_threads_created;
	pthread_mutex_t			dead;
	struct s_philosopher	*philo;
	struct timeval			start;
	int						philo_nbr;
	int						iteration;
	useconds_t				time_to_eat;
	useconds_t				time_to_sleep;
	useconds_t				time_to_die;
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
	int				iteration;
	int				eating_time;
	int				time_wo_eating;
}		t_philo;

/*	ACTIONS.C		*/

int		action_eat(t_philo *philo, t_data *data);
int		action_sleep(t_philo *philo, t_data *data);

/*	CLEAN_EXIT.C	*/

int		print_and_return(void);
void	clean(t_data *data);

/*	INIT.C	*/

int		wait_philo(t_philo *philo);
int		init(t_data *data, int argc, char *argv[]);

/*	LOGS.C	*/

int		print_take(t_data *data, int operation_time, int id, t_philo *philo);
int		print_eat(t_data *data, int operation_time, int id, t_philo *philo);
int		print_sleep(t_data *data, int operation_time, int id, t_philo *philo);
int		print_thinking(t_data *data, int operation_time, int id);

/*	MAIN.C		*/

int		destroy_mutex(t_data *data);

/*	ROUTINE.C	*/

int		is_forks_locked(t_philo philosopher, t_data *data);
int		dying(t_philo philosopher, t_data *data);
void	*routine(void *current_philo);

/*	UTILS.C	*/

int		ft_atoi(const char *str);
int		get_current_operation_time(t_data data);
int		get_time(t_data data, int eating_time);
int		get_forks(t_philo **philosopher);
int		msleep(int time);

#endif
