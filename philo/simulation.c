/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:45 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/21 16:01:37 by jkarippa         ###   ########.fr       */
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
	table->sim_start = get_time(2);
	pthread_mutex_lock(&table->table_mutex);
	table->all_threads_ready = true;
	pthread_mutex_unlock(&table->table_mutex);
	i = 0;
	while (i < table->nbr_of_philo)
	{
		safe_thread(&table->arr_of_philo[i], NULL, NULL, JOIN);
		i++;
	}
}

// long	set_long(pthread_mutex_t *mutex, long *value)
// {
// 	long	ret;

// 	safe_mutex(mutex, LOCK);
// 	ret = *value;
// 	safe_mutex(mutex, UNLOCK);
// 	return (ret);
// }

/*
**	Function for the eat routine of a philosopher
** 1. pick up forks (lock mutexes)
** 2. write status, update last meal time, update meal counter and check if full
** 3. release forks (unlock mutexes)
*/
static void	eat(t_philo *philo)
{
	safe_mutex(&philo->lft_fork->fork, LOCK);
	write_status(FORK_1, philo);
	safe_mutex(&philo->rgt_fork->fork, LOCK);
	write_status(FORK_2, philo);
	safe_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal_time = get_time(2);
	philo->meal_counter++;
	safe_mutex(&philo->philo_mutex, UNLOCK);
	write_status(EAT, philo);
	usleep(philo->table->time_to_eat);
	if (philo->table->nbr_of_times_each_philo_mus_eat > 0
		&& philo->meal_counter >= philo->table->nbr_of_times_each_philo_mus_eat)
	{
		safe_mutex(&philo->philo_mutex, LOCK);
		philo->full = true;
		safe_mutex(&philo->philo_mutex, UNLOCK);
	}
	safe_mutex(&philo->lft_fork->fork, UNLOCK);
	safe_mutex(&philo->rgt_fork->fork, UNLOCK);
}

/*
** Function for the think routine of a philosopher 
*/
static void	think(t_philo *philo)
{
	write_status(THINK, philo);
}

/*
** Function to simulate the dinning problem
*/
void	*simulate_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulaion_finished(philo->table))
	{
		//  1. Am i full?
		if (philo->full)
			break ;
		//  2. eat
		eat(philo);
		//  3. sleep
		write_status(SLEEP, philo);
		usleep(philo->table->time_to_sleep);
		//  4. think
		think(philo);
	}
}
