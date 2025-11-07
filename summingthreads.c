#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	sleep(1);
	int index = *(int *)arg;
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += primes[index + i];
	}
	free(arg);
	return NULL;
}

int	main(int ac, char **av)
{
	pthread_t th[10];
	int i;
	for ( i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a))
			perror("Failed to create");
	}
	for (i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL))
			perror("Failed to join");
	}
	
	return (0);
}