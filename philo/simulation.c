/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:45 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/27 18:27:57 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Utility function to initialize the threads, which are the philosophers of the
** simulation
*/
void	create_philosopers(t_table *table)
{
	if (table->nbr_of_times_each_philo_mus_eat == 0)
		return ;
	else if (table->nbr_of_philo <= 0)
		return ;
	else if (table->nbr_of_philo == 1)
		printf("Ohoooooo only 1 philo so only 1 fork!!! I will die!!!!\n");
	else
		printf("Lets rock and roll!!!!\n");
}
