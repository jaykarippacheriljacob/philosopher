/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:43:04 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/27 11:55:12 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Utility function to convert ASCII to long int
*/
long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/*
** Utility wrapper function for safe allocation of malloc
*/
int	safe_malloc(void **ret, size_t bytes)
{
	*ret = malloc(bytes);
	if (*ret == NULL)
	{
		printf("\033[31mError with malloc\n\033[0m");
		return (1);
	}
	return (0);
}

/*
** Utility function for deallocation of the memory upon error / termination of
** the program
*/
void	terminate(t_table *table)
{
	if (table->arr_of_fork)
	{
		free(table->arr_of_fork);
		printf("\nDeallocated memory for the array of forks in the table");
	}
	if (table->arr_of_philo)
	{
		free(table->arr_of_philo);
		printf("\nDeallocated memory for the array of philosopher in the table");
	}
}

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
