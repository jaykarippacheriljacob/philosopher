/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:41:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/21 18:08:45 by jkarippa         ###   ########.fr       */
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
** OPCODE for philosopher status 
*/

typedef enum e_philostatus
{
	FORK_1,
	FORK_2,	
	EAT,
	SLEEP,
	THINK,
	DIED
}						t_philo_status;

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
** Structure representing an individual fork.
**
** fork_id : Unique ID of the fork
** fork    : Mutex to protect access to this fork
*/
typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;

/*
** Structure declaration
*/
typedef struct s_table	t_table;

/*
** Structure representing an individual philosopher.
**
** philo_id             : Unique ID of the philosopher
** thread_id            : The thread representing this philosopher
** table                : Pointer to the shared table structure
** lft_fork, rgt_fork   : Pointers to the left and right forks
** meal_counter         : Number of times the philosopher has eaten
** last_meal_time       : Timestamp of the last meal
** full                 : Indicates if the philosopher is full
** philo_mutex          : Mutex for protecting philosopher-specific data
*/
typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	t_table			*table;
	t_fork			*lft_fork;
	t_fork			*rgt_fork;
	long			meal_counter;
	long			last_meal_time;
	int				full;
	pthread_mutex_t	philo_mutex;
}					t_philo;

/*
** Defining the structure for the table information
**
** nbr_of_philo: number of philosophers
** time_to_die: time (ms) before a philosopher dies if not eating
** time_to_eat: time (ms) a philosopher spends eating
** time_to_sleep: time (ms) a philosopher spends sleeping
** nbr_of_times_each_philo_mus_eat: number of meals required per philosopher
** sim_start: timestamp of simulation start
**
** sim_end: boolean indicating if simulation has ended
**          (a philosopher died or all philosophers are full)
** all_threads_ready: boolean indicating all threads are ready to start
**
** table_mutex: mutex to avoid race conditions while accessing table data
** write_mutex: mutex to synchronize output to the console
**
** arr_of_fork: array of forks
** arr_of_philo: array of philosophers
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
	bool				all_threads_ready;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
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
void					create_philosophers(t_table *table);
void					wait_all_threads(t_table *table);
void					write_status(t_philo_status status, t_philo *philo);
long					get_time(int type);
void					*simulate_philo(void *data);
/*
** Wrapper functions for safe use of  malloc, mutex and threads.
*/

int						safe_malloc(void **ret, size_t bytes);
int						safe_mutex(pthread_mutex_t *mutex, t_opcode code);
int						safe_thread(pthread_t *thread, void *(*func)(void *),
							void *data, t_opcode code);
bool					simulation_finished(t_table *table);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *src);
#endif