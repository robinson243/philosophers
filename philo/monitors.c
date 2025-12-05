/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:45:18 by romukena          #+#    #+#             */
/*   Updated: 2025/12/05 10:49:52 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_simulation(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	free(args->forks);
	free(philos);
}

int	check_death_and_count(t_args *args, int *full)
{
	long	last;
	long	current_time;
	int		i;

	i = 0;
	current_time = get_time();
	while (i < args->philo_count)
	{
		pthread_mutex_lock(&args->print_mutex);
		if (args->finished)
			return (pthread_mutex_unlock(&args->print_mutex), 1);
		last = args->philos[i].last_meal;
		if (last > 0 && current_time - last > args->time_to_die)
		{
			printf("%ld philosopher [%d] died\n", current_time
				- args->start_time, args->philos[i].id);
			args->finished = 1;
			return (pthread_mutex_unlock(&args->print_mutex), 1);
		}
		if (args->must_eat > 0 && args->philos[i].eat_count < args->must_eat)
			*full = 0;
		pthread_mutex_unlock(&args->print_mutex);
		i++;
	}
	return (0);
}

void	*monitor_philosophers(void *arg)
{
	t_args	*args;
	int		full;

	args = (t_args *)arg;
	while (1)
	{
		full = 1;
		if (check_death_and_count(args, &full))
			return (NULL);
		if (args->must_eat > 0 && full == 1)
		{
			pthread_mutex_lock(&args->print_mutex);
			args->finished = 1;
			pthread_mutex_unlock(&args->print_mutex);
			return (NULL);
		}
		usleep(10);
	}
}
