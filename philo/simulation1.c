/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:45 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/20 16:30:34 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** A helper function to reduce the number of lines in create_n_dine_philosophers.
*/
void	sub_create_n_dine_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		safe_thread(&table->arr_of_philo[i].thread_id, simulate_philo,
			&table->arr_of_philo[i], CREATE);
		i++;
	}
}

/*
** Function to initialize the threads, which are the philosophers of the
** simulation
*/
void	create_n_dine_philosophers(t_table *table)
{
	int	i;

	if (table->nbr_of_times_each_philo_mus_eat == 0)
		return ;
	else if (table->nbr_of_philo <= 0)
		return ;
	else if (table->nbr_of_philo == 1)
	{
		safe_thread(&table->arr_of_philo[0].thread_id,
			alone_philo, &table->arr_of_philo[0], CREATE);
	}
	else
	{
		sub_create_n_dine_philosophers(table);
	}
	safe_mutex(&table->table_mutex, LOCK);
	table->sim_start = get_time(2);
	table->all_threads_ready = true;
	safe_mutex(&table->table_mutex, UNLOCK);
	safe_thread(&table->monitor, monitor_philo, table, CREATE);
	i = -1;
	while (++i < table->nbr_of_philo)
		safe_thread(&table->arr_of_philo[i].thread_id, NULL, NULL, JOIN);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}
// void	create_philosophers(t_table *table)
// {
// 	int	i;

// 	if (table->nbr_of_times_each_philo_mus_eat == 0)
// 		return ;
// 	else if (table->nbr_of_philo <= 0)
// 		return ;
// 	else if (table->nbr_of_philo == 1)
// 		printf("Ohoooooo only 1 philo so only 1 fork!!! I will die!!!!\n");
// 	else
// 	{
// 		i = 0;
// 		while (i < table->nbr_of_philo)
// 		{
// 			safe_thread(&table->arr_of_philo[i].thread_id, simulate_philo,
// 				&table->arr_of_philo[i], CREATE);
// 			i++;
// 		}
// 		printf("Lets rock and roll!!!!\n");
// 	}
// 	table->sim_start = get_time(2);
// 	safe_mutex(&table->table_mutex, LOCK);
// 	printf("table_mutex locked\n");
// 	table->all_threads_ready = true;
// 	safe_mutex(&table->table_mutex, UNLOCK);
// 	printf("table_mutex unlocked\n");
// 	i = 0;
// 	while (i < table->nbr_of_philo)
// 	{
// 		safe_thread(&table->arr_of_philo[i].thread_id, NULL, NULL, JOIN);
// 		i++;
// 	}
// }

// long	set_long(pthread_mutex_t *mutex, long *value)
// {
// 	long	ret;

// 	safe_mutex(mutex, LOCK);
// 	ret = *value;
// 	safe_mutex(mutex, UNLOCK);
// 	return (ret);
// }
