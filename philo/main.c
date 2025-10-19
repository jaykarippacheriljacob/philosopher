/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:51:44 by jkarippa          #+#    #+#             */
/*   Updated: 2025/10/19 18:14:43 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

void	*count_to_100(void *arg)
{
	int	i;

	i = 1;
	(void)arg;
	while (i <= 5)
	{
		printf("%d\n", i);
		i++;
	}
	printf("The count has finished\n");
	return (NULL);
}

void	*print_hello(void *arg)
{
	int	i;

	(void)arg;
	i = 0;
	while (i < 5)
	{
		printf("Hello World!\n");
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_1;
	pthread_t	thread_2;

	pthread_create(&thread_1, NULL, count_to_100, NULL);
	pthread_create(&thread_2, NULL, print_hello, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	return (0);
}
