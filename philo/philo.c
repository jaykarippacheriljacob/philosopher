/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:35:09 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/27 15:48:34 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;
	t_philo	*philo;

	if (arg_checker(argc, argv))
	{
		if (parsing(argc, argv, &table))
			return (1);
		if (data_init(&table))
		{
			terminate(&table);
			return (1);
		}
		printf("philo = %ld\n", table.nbr_of_philo);
		printf("ttd = %ld\n", table.time_to_die);
		printf("tte = %ld\n", table.time_to_eat);
		printf("tts = %ld\n", table.time_to_sleep);
		printf("notepme = %ld\n", table.nbr_of_times_each_philo_mus_eat);
		printf("***************************");
		i = 0;
		while (i < table.nbr_of_philo)
		{
			philo = table.arr_of_philo + i;
			printf("\nPhilo : %d\n", philo->philo_id);
			printf("Left_fork = %d\n", philo->lft_fork->fork_id);
			printf("Right_fork = %d\n", philo->rgt_fork->fork_id);
			i++;
		}
		printf("***************************");
	}
	else
		return (1);
	terminate(&table);
	return (0);
}
