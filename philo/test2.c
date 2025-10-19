/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:26:07 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/19 20:27:32 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define BIG 1000000000UL

typedef struct s_utils
{
	__uint32_t		*a;
	pthread_mutex_t	*a_lock;
}					t_utils;

void	*change_a(void *arg)
{
	__uint32_t	i;
	t_utils		*util;

	util = (t_utils *)arg;
	i = 0;
	pthread_mutex_lock(util->a_lock);
	while (i < BIG)
	{
		(*(util->a))++;
		i++;
	}
	pthread_mutex_unlock(util->a_lock);
	return (NULL);
}

int	main(void)
{
	pthread_t		thread_1;
	pthread_t		thread_2;
	__uint32_t		a;
	t_utils			util;
	pthread_mutex_t	a_lock;

	a = 0;
	util.a = &a;
	pthread_mutex_init(&a_lock, NULL);
	util.a_lock = &a_lock;
	pthread_create(&thread_1, NULL, change_a, &util);
	pthread_create(&thread_2, NULL, change_a, &util);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	printf("a is: %u\n", a);
}
