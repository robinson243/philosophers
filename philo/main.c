/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:43:05 by romukena          #+#    #+#             */
/*   Updated: 2025/11/25 02:38:39 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_threads(pthread_t *threads, int created, t_args *args)
{
	int	i;

	i = 0;
	args->finished = 1;
	while (i < created)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static int	create_philo_threads(t_args *args, t_philo *philos,
		pthread_t *threads)
{
	int	i;
	int	ret;

	i = 0;
	while (i < args->philo_count)
	{
		ret = pthread_create(&threads[i], NULL, philo_life, (void *)&philos[i]);
		if (ret != 0)
		{
			ft_putstrfd("Error: pthread_create failed\n", 2);
			cleanup_threads(threads, i, args);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}

static int	join_all_threads(pthread_t *threads, pthread_t monitor,
		int philo_count)
{
	int	i;
	int	ret;
	int	error;

	i = 0;
	error = 0;
	while (i < philo_count)
	{
		ret = pthread_join(threads[i], NULL);
		if (ret != 0)
		{
			ft_putstrfd("Warning: pthread_join failed\n", 2);
			error = 1;
		}
		i++;
	}
	ret = pthread_join(monitor, NULL);
	if (ret != 0)
	{
		ft_putstrfd("Warning: monitor pthread_join failed\n", 2);
		error = 1;
	}
	return (error);
}

int	launch_simulation(t_args *args, t_philo *philos, pthread_t *threads)
{
	pthread_t	monitor_thread;
	int			ret;

	args->start_time = get_time();
	if (create_philo_threads(args, philos, threads) == 1)
		return (1);
	usleep(5000);
	ret = pthread_create(&monitor_thread, NULL, monitor_philosophers,
			(void *)args);
	if (ret != 0)
	{
		ft_putstrfd("Error: monitor pthread_create failed\n", 2);
		cleanup_threads(threads, args->philo_count, args);
		return (1);
	}
	return (join_all_threads(threads, monitor_thread, args->philo_count));
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		*philos;
	pthread_t	*threads;
	int			ret;

	philos = NULL;
	threads = NULL;
	if (parse_args(argc, argv, &args) == 1)
		return (1);
	if (init_mutexes(&args) == 1)
		return (1);
	if (init_philosophers(&args, &philos) == 1)
		return (clean_simulation(&args, NULL), 1);
	args.philos = philos;
	threads = malloc(sizeof(pthread_t) * args.philo_count);
	if (!threads)
		return (clean_simulation(&args, philos), 1);
	ret = launch_simulation(&args, philos, threads);
	clean_simulation(&args, philos);
	free(threads);
	return (ret);
}
