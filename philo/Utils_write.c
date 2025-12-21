/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:56:17 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/21 16:03:14 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Utility function to print the status of a philosopher.
**  [timestamp_in_ms] Philosopher [id] has a fork
**  [timestamp_in_ms] Philosopher [id] is eating
**  [timestamp_in_ms] Philosopher [id] is sleeping
**  [timestamp_in_ms] Philosopher [id] is thinking
**  [timestamp_in_ms] Philosopher [id] died
*/
void	write_status(t_philo_status status, t_philo *philo)
{
	long	time_elapsed;
	bool	sim_finished;

	time_elapsed = get_time(1) - philo->table->sim_start;
	sim_finished = simulation_finished(philo->table);
	safe_mutex(&philo->table->write_mutex, LOCK);
	if (!sim_finished)
	{
		safe_mutex(&philo->table->write_mutex, UNLOCK);
		return ;
	}
	if (status == FORK_1 || status == FORK_2)
		printf("%ld %d has taken a fork\n", time_elapsed,
			philo->philo_id);
	else if (status == EAT)
		printf("%ld %d is eating\n", time_elapsed, philo->philo_id);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", time_elapsed,
			philo->philo_id);
	else if (status == THINK)
		printf("%ld %d is thinking\n", time_elapsed,
			philo->philo_id);
	else if (status == DIED)
		printf("%ld %d died\n", time_elapsed, philo->philo_id);
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
