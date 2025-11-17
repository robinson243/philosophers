#include "philo.h"

int	init_philosophers(t_args *args, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * args->philo_count);
	if (!*philos)
		return (1);
	while (i < args->philo_count)
	{
		(*philos)[i].id = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_meal = get_time();
		(*philos)[i].finished = 0;
		(*philos)[i].left_fork = &args->forks[i];
		(*philos)[i].right_fork = &args->forks[(i + 1) % args->philo_count];
		i++;
	}
	return (0);
}

void ft_usleep(long time)
{
	long actual;
	
	actual = get_time();
	while ((get_time() - actual) < time)
	{
		usleep(100);
	}
}

