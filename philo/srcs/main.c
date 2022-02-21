/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:51:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/18 13:25:07 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *philosopher)
{
	t_philosopher	*current_philosopher;
	int				i;
	unsigned int	wait_time;

	current_philosopher = philosopher;
	i = 0;
	wait_time = 100;
	printf("Salut\n");
	//usleep(10000);
	return ((void *) 1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		error;

	error = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error\nWrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		printf("Error\nYou need at least one philosopher !\n");
		return (EXIT_FAILURE);
	}
	error = init(&data, argv);
	if (error == 1)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	return (1);
}
