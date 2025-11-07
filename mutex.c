/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:21:36 by romukena          #+#    #+#             */
/*   Updated: 2025/11/07 11:15:08 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Sert a faire patienter les threads entre eux car ils partagent la meme memoire. les pthread_join eux servent a dire au main de patentier que le thread s'execute.

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	for (int i = 0; i < 1000000.; i++)
	{
		pthread_mutex_lock(&mutex);
		mails ++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int ac, char **av)
{
	pthread_t p1, p2;
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&p1, NULL, &routine , NULL))
		return 1;
	if (pthread_create(&p2, NULL, &routine , NULL))
		return 2;
	if (pthread_join(p1, NULL))
		return 3;
	if (pthread_join(p2, NULL))
		return 4;
	pthread_mutex_destroy(&mutex);
	printf("Numbers of msiils %d\n", mails);
	return 0;
}