/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:44:55 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 11:33:13 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function to inspect the arguments passed by the user for the operation.
*/
int	arg_checker(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
	{
		printf("\033[31mInvalid no.of arguments!\033[0m");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!(int_checker(argv[i])) || argv[i][0] == '-')
		{
			printf("\033[31mInvalid argument type!\033[0m");
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** Utility function to check if the argument is an integer or not
*/
int	int_checker(char *n)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 0;
	if (!n || n[0] == '\0')
		return (0);
	if (n[i] == '-' || n[i] == '+')
	{
		i++;
		sign = 1;
		if (n[i] == '\0')
			return (0);
	}
	while (n[i] != '\0')
	{
		if (n[i] > '9' || n[i] < '0')
			return (0);
		i++;
	}
	nbr = ft_atol(n);
	if (nbr > INT_MAX || nbr < INT_MIN || (i - sign) > 10)
		return (0);
	return (1);
}
