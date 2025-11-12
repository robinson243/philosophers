/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:41:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 17:29:07 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) *1000 + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (table->someone_died == 0)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&table->forks[philo->right_fork]);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(&table->forks[philo->left_fork]);
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&table->forks[philo->left_fork]);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(&table->forks[philo->right_fork]);
			print_status(philo, "has taken a fork");
		}
		pthread_mutex_lock(&table->death_lock);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&table->death_lock);
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
