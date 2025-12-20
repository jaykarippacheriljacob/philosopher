/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:45 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/20 16:33:00 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function to initialize the threads, which are the philosophers of the
** simulation
*/
void	create_philosopers(t_table *table)
{
	int	i;

	if (table->nbr_of_times_each_philo_mus_eat == 0)
		return ;
	else if (table->nbr_of_philo <= 0)
		return ;
	else if (table->nbr_of_philo == 1)
		printf("Ohoooooo only 1 philo so only 1 fork!!! I will die!!!!\n");
	else
	{
		i = 0;
		while (i < table->nbr_of_philo)
		{
			safe_thread(&table->arr_of_philo[i], simulate_philo,
				&table->arr_of_philo[i], CREATE);
			i++;
		}
		printf("Lets rock and roll!!!!\n");
	}
	safe_mutex(&table->all_threads_ready, LOCK);
}

/*
** Function to simulate the dinning problem
*/
void	*simulate_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
}
