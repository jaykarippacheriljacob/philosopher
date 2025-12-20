/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_synchro_monitor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:36:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/20 18:12:19 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex(&mutex->lock, LOCK);
	*dest = value;
	safe_mutex(&mutex->lock, UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool *src)
{
	bool	value;

	safe_mutex(&mutex->lock, LOCK);
	value = *src;
	safe_mutex(&mutex->lock, UNLOCK);
	return (value);
}

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
