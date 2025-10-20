/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:27:37 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 11:14:20 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(int argc, char **argv, t_table *table)
{
	if (argc == 6)
		table->nbr_of_times_each_philo_mus_eat = ft_atol(argv[5]);
	else
		table->nbr_of_times_each_philo_mus_eat = -1;
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
