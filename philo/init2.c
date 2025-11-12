/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:20:42 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 17:28:31 by romukena         ###   ########.fr       */
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

void	print_status(t_philo *philo, char *status)
{
	t_table		*table;
	long long	timestamp;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	if (table->someone_died == 0)
	{
		timestamp = get_time() - table->start_sim;
		printf("%lld philosophe[%d] %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&table->print_lock);
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->len_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	free(table->forks);
	free(table->philos);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	if (create_philosophers_threads(table) == 0)
		return (0);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0)
	{
		cleanup(table);
		return (0);
	}
	while (i < table->len_philo)
	{
		pthread_join(table->philos[i].philo_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	cleanup(table);
	return (1);
}
