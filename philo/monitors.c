/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:45:18 by romukena          #+#    #+#             */
/*   Updated: 2025/11/20 01:57:27 by romukena         ###   ########.fr       */
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

void	*monitor_philosophers(void *arg)
{
	t_args	*args;
	int		i;
	long	last;

	args = (t_args *)arg;
	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			pthread_mutex_lock(&args->print_mutex);
			last = args->philos[i].last_meal;
			if (!args->finished && get_time() - last > args->time_to_die)
			{
				printf("%ld philosopher [%d] died\n", get_time()
					- args->start_time, args->philos[i].id);
				args->finished = 1;
				pthread_mutex_unlock(&args->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&args->print_mutex);
			i++;
		}
		usleep(1000);
	}
}
