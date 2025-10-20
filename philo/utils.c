/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:43:04 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/21 00:35:04 by jkarippa         ###   ########.fr       */
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
** Utility function for safe allocation of malloc
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
** Helper function for dealing with errors from mutex uses
*/
static int	handle_mutex_error(int status, t_opcode code)
{
	if (status == 0)
		return (0);
}

/*
** Utility function for safe handling of mutex
*/
void	safe_mutex(pthread_mutex_t *mutex, t_opcode code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		printf("Wrong opcode for the mutex handle");
}
