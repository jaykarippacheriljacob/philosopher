/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:44:55 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/19 23:28:11 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function to inspect the arguments passed by the user for the operation.
*/
int	arg_checker(int argc, char **argv)
{
	int	i;
	int	j;

	if (!(argc == 5 || argc == 6))
	{
		printf("\033[31mInvalid no.of arguments!\033[0m");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("\033[31mInvalid argument type!\033[0m");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
