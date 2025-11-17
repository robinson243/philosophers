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

void philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] has taken a fork\n",get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] has taken a fork\n",get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] is eating\n",get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	philo->last_meal = get_time();
	philo->eat_count += 1;
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] is sleeping\n",get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_sleep);
}