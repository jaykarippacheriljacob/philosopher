/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:41:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/20 11:27:38 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*
** Defining the structure for induvidual fork
*/
typedef struct s_fork
{
	int					fork_id;
	pthread_mutex_t		fork;
}						t_fork;

/*
** Structure declaration
*/
typedef struct s_table	t_table;

/*
** Defining the structure for induvidual philosopher
*/
typedef struct s_philo
{
	int					philo_id;
	pthread_t			thread_id;
	t_table				*table;
	t_fork				*lft_fork;
	t_fork				*rgt_fork;
	long				meal_counter;
	long				last_meal_time;
	int					full;
}						t_philo;

/*
** Defining the structure for the table information
*/
typedef struct s_table
{
	long				nbr_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_of_times_each_philo_mus_eat;
	long				sim_start;
	long				sim_end;
	t_fork				*arr_of_fork;
	t_philo				*arr_of_philo;
}						t_table;

/*
** Function declarations
*/
int						arg_checker(int argc, char **argv);
void					parsing(int argc, char **argv, t_table *table);
long					ft_atol(const char *str);
int						int_checker(char *n);
#endif