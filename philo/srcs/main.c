/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:51:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/02/28 14:47:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	if (init(&data, argc, argv) == 1)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	return (1);
}
