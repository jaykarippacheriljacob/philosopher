/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:35:09 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 11:17:00 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (arg_checker(argc, argv))
	{
		printf("SUCCESS\n");
		parsing(argc, argv, &table);
		printf("nbr = %ld", table.nbr_of_times_each_philo_mus_eat);
	}
	else
		return (1);
	return (0);
}
