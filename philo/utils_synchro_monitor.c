/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_synchro_monitor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:36:27 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/20 13:13:17 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Setter function to safely set the boolean value with mutex lock
*/
// void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
// {
// 	safe_mutex(mutex, LOCK);
// 	*dest = value;
// 	safe_mutex(mutex, UNLOCK);
// }

/*
** Getter function to safely get the boolean value with mutex lock
*/
// bool	get_bool(pthread_mutex_t *mutex, bool *src)
// {
// 	bool	value;

// 	safe_mutex(mutex, LOCK);
// 	value = *src;
// 	safe_mutex(mutex, UNLOCK);
// 	return (value);
// }

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

/*
** SpinLock to synchornize all philosophers to start at the same time
*/
void	wait_all_threads(t_table *table)
{
	while (true)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->all_threads_ready)
		{
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->table_mutex);
	}
}

/*
**
*/
static bool	philo_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;
	bool	full;

	safe_mutex(&philo->philo_mutex, LOCK);
	full = philo->full;
	safe_mutex(&philo->philo_mutex, UNLOCK);
	if (full)
		return (false);
	current_time = get_time(2);
	safe_mutex(&philo->philo_mutex, LOCK);
	time_since_last_meal = current_time - philo->last_meal_time;
	safe_mutex(&philo->philo_mutex, UNLOCK);
	if (time_since_last_meal >= philo->table->time_to_die)
		return (true);
	return (false);
}

/*
** 
*/
bool	all_threads_running(pthread_mutex_t *mutex,
							long *no_of_threads_running, long nbr_of_philo)
{
	bool	all_running;

	safe_mutex(mutex, LOCK);
	if (*no_of_threads_running == nbr_of_philo)
		all_running = true;
	else
		all_running = false;
	safe_mutex(mutex, UNLOCK);
	return (all_running);
}

/*
** Function for the monitor thread to check for philosopher's death and
** end the simulation
*/
void	*monitor_philo(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->no_of_threads_running, table->nbr_of_philo))
		usleep(100);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->nbr_of_philo)
		{
			if (philo_dead(table->arr_of_philo + i))
			{
				safe_mutex(&table->table_mutex, LOCK);
				if (!table->sim_end)
				{
					table->sim_end = true;
					safe_mutex(&table->table_mutex, UNLOCK);
					write_status(DIED, table->arr_of_philo + i);
				}
				else
					safe_mutex(&table->table_mutex, UNLOCK);
			}
		}
		check_all_full(table);
		usleep(1000);
	}
	return (NULL);
}
