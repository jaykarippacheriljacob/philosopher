/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_synchro_monitor1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:13:02 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/20 13:54:51 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function to check if all philosophers are full and end simulation if true
*/
void	check_all_full(t_table *table)
{
	int	full_count;
	int	i;

	full_count = 0;
	i = 0;
	while (i < table->nbr_of_philo)
	{
		safe_mutex(&table->arr_of_philo[i].philo_mutex, LOCK);
		if (table->arr_of_philo[i].full)
			full_count++;
		safe_mutex(&table->arr_of_philo[i].philo_mutex, UNLOCK);
		i++;
	}
	if (table->nbr_of_times_each_philo_mus_eat > 0
		&& full_count == table->nbr_of_philo)
	{
		safe_mutex(&table->table_mutex, LOCK);
		table->sim_end = true;
		safe_mutex(&table->table_mutex, UNLOCK);
	}
}

/*
** Function to check if the simulation has finished
** i.e., if a philosopher has died or all philosophers are full
*/
bool	simulation_finished(t_table *table)
{
	bool	finished;

	safe_mutex(&table->table_mutex, LOCK);
	finished = table->sim_end;
	safe_mutex(&table->table_mutex, UNLOCK);
	return (finished);
}
// bool	simulation_finished(t_table *table)
// {
// 	return (get_bool(&table->table_mutex, &table->sim_end));
// }