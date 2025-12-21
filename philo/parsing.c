/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:27:37 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/21 15:35:23 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function for pasing the initial input data to the structure table.
** It is to be noted that usleep is not precise for short times < 60ms.
** convert to s to ms.
*/
int	parsing(int argc, char **argv, t_table *table)
{
	if (argc == 6)
		table->nbr_of_times_each_philo_mus_eat = ft_atol(argv[5]);
	else
		table->nbr_of_times_each_philo_mus_eat = -1;
	table->nbr_of_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
	{
		printf("\033[31mPlease use timestamps larger than 60ms.\n\033[0m");
		return (1);
	}
	return (0);
}

/*
** Helper function to assign forks to each philosopher
** Here to avoid the dead lock we use the odd even solution. i.e,
** the philoshoper even take left first and the odd takes the right fork
** This potentially makes sure that atleast one philosophor is there with out
** potential deadlock.
*/
void	assign_fork(t_philo *philo, t_fork *fork)
{
	int	n;
	int	i;

	n = philo->table->nbr_of_philo;
	i = philo->philo_id - 1;
	if (philo->philo_id % 2 == 0)
	{
		philo->lft_fork = &fork[i];
		philo->rgt_fork = &fork[(i + 1) % n];
	}
	else
	{
		philo->rgt_fork = &fork[i];
		philo->lft_fork = &fork[(i + 1) % n];
	}
}

/*
** Helper function for initializing each philosopher from the array of
** philosohpers
*/
static void	philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		philo = &table->arr_of_philo[i];
		philo->full = false;
		philo->meal_counter = 0;
		philo->philo_id = i + 1;
		philo->table = table;
		assign_fork(philo, table->arr_of_fork);
		safe_mutex(&philo->philo_mutex, INIT);
		i++;
	}
}

/*
** Function for the initializing the table.
*/
int	data_init(t_table *table)
{
	int	i;

	table->sim_end = false;
	table->all_threads_ready = false;
	if (safe_malloc((void **)&table->arr_of_philo, sizeof(t_philo)
			* table->nbr_of_philo))
		return (1);
	if (safe_malloc((void **)&table->arr_of_fork, sizeof(t_fork)
			* table->nbr_of_philo))
		return (1);
	if ((safe_mutex(&table->table_mutex, INIT)))
		return (1);
	if ((safe_mutex(&table->write_mutex, INIT)))
		return (1);
	i = 0;
	while (i < table->nbr_of_philo)
	{
		if ((safe_mutex(&table->arr_of_fork[i].fork, INIT)))
			return (1);
		table->arr_of_fork[i].fork_id = i + 1;
		i++;
	}
	philo_init(table);
	return (0);
}

// C program to check the size of 'long'
//  data type
// #include <stdio.h>

// int	main(void)
// {
// 	printf("Size of int = %ld\n", sizeof(int));
// 	printf("Size of long = %ld\n", sizeof(long));
// 	printf("Size of long long = %ld", sizeof(long long));
// }