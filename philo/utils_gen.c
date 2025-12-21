/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:43:04 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/20 18:55:18 by jkarippa         ###   ########.fr       */
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
** Utility function to get the current time in
** 1->seconds
** 2->milliseconds or
** 3->microseconds
*/
long	get_time(int type)
{
	struct timeval	time;
	long			ms_time;

	gettimeofday(&time, NULL); // Check if a checker is needed for error or not.
	if (type == 1)
		ms_time = time.tv_sec;
	else if (type == 2)
		ms_time = (time.tv_sec * 1e3) + (time.tv_usec / 1e3);
	else if (type == 3)
		ms_time = (time.tv_sec * 1e6) + time.tv_usec;
	return (ms_time);
}
