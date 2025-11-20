/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:43:05 by romukena          #+#    #+#             */
/*   Updated: 2025/11/20 22:49:08 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_simulation(t_args *args, t_philo *philos, pthread_t *threads)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	args->start_time = get_time();
	while (i < args->philo_count)
	{
		pthread_create(&threads[i], NULL, philo_life, (void *)&philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_philosophers, (void *)args);
	i = 0;
	while (i < args->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		*philos;
	pthread_t	*threads;

	philos = NULL;
	if (parse_args(argc, argv, &args) == 1)
		return (1);
	if (init_mutexes(&args) == 1)
		return (1);
	if (init_philosophers(&args, &philos) == 1)
		return (1);
	args.philos = philos;
	threads = malloc(sizeof(pthread_t) * args.philo_count);
	if (!threads)
		return (1);
	launch_simulation(&args, philos, threads);
	clean_simulation(&args, philos);
	free(threads);
	return (0);
}

/*
int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	philos = NULL;
	if (parse_args(argc, argv, &args) == 1)
		return (1);
	if (init_mutexes(&args) == 1)
		return (1);
	if (init_philosophers(&args, &philos) == 1)
		return (1);
	args.philos = philos;
	threads = malloc(sizeof(pthread_t) * args.philo_count);
	if (!threads)
		return (1);
	args.start_time = get_time();
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, philo_life, (void *)&philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_philosophers, (void *)&args);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	clean_simulation(&args, philos);
	free(threads);
	return (0);
} */
