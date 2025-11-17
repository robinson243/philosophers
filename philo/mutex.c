#include "philo.h"

void	destroy_all_mutexes(pthread_mutex_t *tab, int i)
{
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&tab[i]);
	}
	free(tab);
}

int	init_mutexes(t_args *args)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if (!forks)
		return (1);
	while (i < args->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_all_mutexes(forks, i), 1);
		i++;
	}
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
		return (destroy_all_mutexes(forks, i), 1);
	args->forks = forks;
	return (0);
}