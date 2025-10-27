/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:19:01 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/27 10:33:06 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	else if (status == EDEADLK)
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
