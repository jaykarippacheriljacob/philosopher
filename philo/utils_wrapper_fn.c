/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wrapper_fn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:19:01 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/20 16:35:03 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Helper function for dealing with errors from mutex uses
*/
static int	handle_mutex_error(int status, t_opcode code)
{
	if (status == 0)
		return (0);
	if (EINVAL == status && (LOCK == code || UNLOCK == code))
		return (printf("The value specified by mutex is invalid"));
	else if (EINVAL == status && INIT == code)
		return (printf("The value specified by the attribute is invalid"));
	else if (EDEADLK == status)
		return (printf("Deadlk would occur if thread blocked waits for mutex"));
	else if (EPERM == status)
		return (printf("Current thread does not hold lock on mutex"));
	else if (ENOMEM == status)
		return (printf("Process can't allocate enough memory for new mutex"));
	else
		return (printf("Mutex is locked"));
}

/*
** Utility wrapper function for safe handling of mutex
*/
int	safe_mutex(pthread_mutex_t *mutex, t_opcode code)
{
	int	status;

	if (code == LOCK)
		status = handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		status = handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		status = handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		status = handle_mutex_error(pthread_mutex_destroy(mutex), code);
	else
		status = printf("Wrong opcode for the mutex handle");
	return (status);
}

/*
** Helper function for dealing with errors from threads.
*/
static int	handle_thread_error(int status, t_opcode code)
{
	if (status == 0)
		return (0);
	if (status == EAGAIN)
		return (printf("No resources to create another thread"));
	else if (status == EPERM)
		return (printf("Caller does not have appropriate permission"));
	else if (status == EINVAL && code == CREATE)
		return (printf("Value specified by attribute is invalid"));
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		return (printf("Value specified by the thread is not joinable"));
	else if (status == ESRCH)
		return (printf("No thread for the specified thread id"));
	else
		return (printf("Deadlock occured"));
}

/*
** Utility wrapper function for safe handling of threads.
*/
int	safe_thread(pthread_t *thread, void *(*func)(void *), void *data,
		t_opcode code)
{
	int	status;

	if (code == CREATE)
		status = handle_thread_error(pthread_create(thread, NULL, func, data),
				code);
	else if (code == JOIN)
		status = handle_thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		status = handle_thread_error(pthread_detach(*thread), code);
	else
		status = printf("Wrong opcode for safe_thread");
	return (status);
}
