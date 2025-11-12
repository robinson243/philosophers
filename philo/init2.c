/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:20:42 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 13:27:07 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_table *main)
{
	int	i;

	i = 0;
	while (i < main->len_philo)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&main->print_lock);
	pthread_mutex_destroy(&main->death_lock);
	free(main->forks);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) *1000 + (tv.tv_usec / 1000));
}

int	init_everything(t_table *table, char **av)
{
	int		i;
	t_philo	*philos;

	i = 0;
	init_table(table, av);
	if (init_forks_mutex(table) == 0 || init_mutex(table) == 0)
		return (0);
	philos = init_tab_philo(table, table->len_philo);
	if (!philos)
		return (0);
	table->start_sim = get_time();
	while (i < table->len_philo)
	{
		philos[i].last_meal = table->start_sim;
		i++;
	}
	table->philos = philos;
	return (1);
}

void	ft_usleep(long ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *status)
{
	t_table		*table;
	long long	timestamp;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	if (table->someone_died == 0)
	{
		timestamp = get_time() - table->start_sim;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&table->print_lock);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (table->someone_died == 0)
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
		philo->last_meal = get_time();
		print_status(philo, "is eating");
		ft_usleep(table->time_to_eat);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		print_status(philo, "is sleeping");
		ft_usleep(table->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	create_philosophers_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->len_philo)
	{
		if (pthread_create(&table->philos[i].philo_id, NULL,
				philosopher_routine, &table->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		elapsed;
	int		i;

	i = 0;
	table = (t_table *)arg;
	while (table->someone_died == 0)
	{
		i = 0;
		while (i < table->len_philo)
		{
			elapsed = get_time() - table->philos[i].last_meal;
			if (elapsed > table->time_to_die)
			{
				print_status(&table->philos[i], "is died");
				table->someone_died = 1;
				return ;
			}
			usleep(1000);
			i++;
		}
	}
	return (NULL);
}
