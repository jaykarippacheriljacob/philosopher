/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:41:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/27 12:00:01 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*
** OPCODE for mutex | thread functions
*/
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opcode;
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
** End_sim if a philo dies or all philo are full
*/
typedef struct s_table
{
	long				nbr_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_of_times_each_philo_mus_eat;
	long				sim_start;
	bool				sim_end;
	t_fork				*arr_of_fork;
	t_philo				*arr_of_philo;
}						t_table;
/*
** Function declarations
*/

int						arg_checker(int argc, char **argv);
int						parsing(int argc, char **argv, t_table *table);
long					ft_atol(const char *str);
int						int_checker(char *n);
int						data_init(t_table *table);
void					terminate(t_table *table);
/*
** Wrapper functions for safe use of  malloc, mutex and threads.
*/

int						safe_malloc(void **ret, size_t bytes);
int						safe_mutex(pthread_mutex_t *mutex, t_opcode code);
int						safe_thread(pthread_t *thread, void *(*func)(void *),
							void *data, t_opcode code);
#endif