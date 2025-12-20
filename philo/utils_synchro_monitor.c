/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_synchro_monitor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:36:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/20 18:15:52 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *src)
{
	bool	value;

	safe_mutex(mutex, LOCK);
	value = *src;
	safe_mutex(mutex, UNLOCK);
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
