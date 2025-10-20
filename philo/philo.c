/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:35:09 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 16:53:23 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (arg_checker(argc, argv))
	{
		if (parsing(argc, argv, &table))
			return (1);
		printf("philo = %ld\n", table.nbr_of_philo);
		printf("ttd = %ld\n", table.time_to_die);
		printf("tte = %ld\n", table.time_to_eat);
		printf("tts = %ld\n", table.time_to_sleep);
		printf("notepme = %ld\n", table.nbr_of_times_each_philo_mus_eat);
	}
	else
		return (1);
	return (0);
}
