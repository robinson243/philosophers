/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:20:42 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 12:36:12 by romukena         ###   ########.fr       */
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

// int	create_philos_threads(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->len_philo)
// 	{
// 		if (pthread_create(&table->philos[i], NULL, ) != 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }