/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:43:04 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 18:07:46 by jkarippa         ###   ########.fr       */
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
