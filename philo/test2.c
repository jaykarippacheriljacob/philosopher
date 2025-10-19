/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:26:07 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/19 20:00:30 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define BIG 1000000000UL

void	*change_a(void *arg)
{
	__uint32_t	*a;
	__uint32_t	i;

	a = (__uint32_t *)arg;
	i = 0;
	while (i < BIG)
	{
		(*a)++;
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_1;
	pthread_t	thread_2;
	__uint32_t	a;

	a = 0;
	pthread_create(&thread_1, NULL, change_a, &a);
	pthread_create(&thread_2, NULL, change_a, &a);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	printf("a is: %u\n", a);
}
