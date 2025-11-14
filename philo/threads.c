/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:42:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/14 01:59:04 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_table		*table;
	long long	elapsed;
	int			i;

	table = (t_table *)arg;
	while (1)
	{
		if (table->someone_died)
			return (NULL);
		i = 0;
		while (i < table->len_philo)
		{
			pthread_mutex_lock(&table->death_lock);
			elapsed = get_time() - table->philos[i].last_meal;
			if (elapsed > table->time_to_die && table->someone_died == 0)
			{
				table->someone_died = 1;
				pthread_mutex_unlock(&table->death_lock);
				print_status(&table->philos[i], "is died");
				return (NULL);
			}
			pthread_mutex_unlock(&table->death_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
