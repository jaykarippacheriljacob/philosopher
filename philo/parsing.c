/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:27:37 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 16:55:10 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Fuction for pasing the initial input data to the structure table.
** It is to be noted that usleep is not precise for short times < 60ms.
** convert to s to ms.
*/
int	parsing(int argc, char **argv, t_table *table)
{
	if (argc == 6)
		table->nbr_of_times_each_philo_mus_eat = ft_atol(argv[5]);
	else
		table->nbr_of_times_each_philo_mus_eat = -1;
	table->nbr_of_philo = ft_atol(argv[1]) * 1e3;
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
	{
		printf("\033[31mPlease use timestamps larger than 60ms.\n\033[0m");
		return (1);
	}
	return (0);
}

// C program to check the size of 'long'
//  data type
// #include <stdio.h>

// int	main(void)
// {
// 	printf("Size of int = %ld\n", sizeof(int));
// 	printf("Size of long = %ld\n", sizeof(long));
// 	printf("Size of long long = %ld", sizeof(long long));
// }