/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:45 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/20 13:29:48 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function to simulate the dinning problem for one philosopher alone (edge case)
*/
void	*alone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	safe_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal_time = get_time(2);
	safe_mutex(&philo->philo_mutex, UNLOCK);
	safe_mutex(&philo->table->table_mutex, LOCK);
	philo->table->no_of_threads_running++;
	safe_mutex(&philo->table->table_mutex, UNLOCK);
	write_status(FORK_1, philo);
	while (!simulation_finished(philo->table))
		;
	return (NULL);
}

/*
**	Function for the eat routine of a philosopher
** 1. pick up forks (lock mutexes)
** 2. write status, update last meal time, update meal counter and check if full
** 3. release forks (unlock mutexes)
*/
static void	eat(t_philo *philo)
{
	if (!philo->full)
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
		usleep(philo->table->time_to_eat * 1000);
	}
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
	usleep(THINK_TIME);
}

/*
** Function to simulate the dinning problem
*/
void	*simulate_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	safe_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal_time = get_time(2);
	safe_mutex(&philo->philo_mutex, UNLOCK);
	safe_mutex(&philo->table->table_mutex, LOCK);
	philo->table->no_of_threads_running++;
	safe_mutex(&philo->table->table_mutex, UNLOCK);
	while (!simulation_finished(philo->table))
	{
		eat(philo);
		if (simulation_finished(philo->table))
			break ;
		write_status(SLEEP, philo);
		usleep(philo->table->time_to_sleep * 1000);
		think(philo);
	}
	return (NULL);
}
