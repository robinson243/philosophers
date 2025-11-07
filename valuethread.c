#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	return (void *)result;
	
}

int	main(int ac, char **av)
{
	pthread_t th;
	int	*res;
	srand(time(NULL));
	if (pthread_create(&th, NULL, &roll_dice, NULL))
		return (1);
	if (pthread_join(th, (void **)&res))
		return (2);
	printf("Result : %d\n", *res);
	return (0);
}