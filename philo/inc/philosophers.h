/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:43:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/18 13:25:55 by psaulnie         ###   ########.fr       */
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
	int				left_philo;
	int				right_philo;
}		t_fork;

typedef struct s_data {
	t_fork					*forks;
	struct s_philosopher	*philo;
	struct timeval			start;
	float					total_time;
	int						philo_nbr;
	int						nbr_iter;
	int						err;
}		t_data;

typedef struct s_philosopher
{
	t_data		*data;
	pthread_t	thread_id;
	int			id;
}		t_philosopher;

/*	INIT.C	*/

int		init(t_data *data, char *argv[]);

/*	MAIN.C	*/

void	*routine(void *philosopher);

/*	UTILS.C	*/

int		ft_atoi(const char *str);
int		get_current_operation_time(t_data data);

#endif
