/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:11 by romukena          #+#    #+#             */
/*   Updated: 2025/11/04 16:44:16 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// void	*func1(void *arg)
// {
// 	usleep(10000);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		fprintf(stderr, "\033[91m%s\033[0m\n", (char *)arg);
// 	}
// 	pthread_exit(arg);
// }
// void	*func2(void *arg)
// {
// 	for (int i = 0; i < 10; i++)
// 	{
// 		fprintf(stderr, "\033[95m%s\033[0m\n", (char *)arg);
// 	}
// 	pthread_exit(arg); // sortir du thread et donner une valeur de retour 
// }

// int main(void)
// {
// 	pthread_t t1;
// 	pthread_t t2;

// 	pthread_create(&t1, NULL, func1 , "hello 1"); // creer le thread
// 	pthread_create(&t2, NULL, func2 , "hello 2");

// 	char *s1, *s2;
// 	pthread_join(t1,(void **) &s1); //attendre que le code s'execute 
// 	pthread_join(t2, (void **) &s2);
// 	printf("%s, %s\n", s1, s2);
// }

int main(int ac, char **av)
{
	pthread_t t1;

	pthread_create(&t1, NULL, func , NULL);
	pthread_join(t1, NULL);
	
	return 0;
}

