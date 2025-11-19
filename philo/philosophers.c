/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:44:02 by romukena          #+#    #+#             */
/*   Updated: 2025/11/19 03:14:04 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] has taken a fork\n", get_time()
		- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	if (philo->args->philo_count == 1)
	{
		ft_usleep(philo->args->time_to_die + 1);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] has taken a fork\n", get_time()
		- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] is eating\n", get_time()
		- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	philo->last_meal = get_time();
	philo->eat_count += 1;
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] is sleeping\n", get_time()
		- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld philosopher [%d] is thinking\n", get_time()
		- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->args->philo_count == 1)
	{
		philo_think(philo);
		philo_take_forks(philo);
		return (NULL);
	}
	while (philo->args->finished == 0)
	{
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
