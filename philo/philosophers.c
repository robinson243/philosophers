/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:44:02 by romukena          #+#    #+#             */
/*   Updated: 2025/11/28 13:18:54 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	lock_forks_in_order(philo, &first, &second);
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
		printf("%ld philosopher [%d] has taken a fork\n", get_time()
			- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	if (philo->args->philo_count == 1)
		return (ft_usleep(philo->args->time_to_die + 1, philo),
			pthread_mutex_unlock(first), (void)0);
	pthread_mutex_lock(second);
	philo->left_fork = first;
	philo->right_fork = second;
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
		printf("%ld philosopher [%d] has taken a fork\n", get_time()
			- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
		printf("%ld philosopher [%d] is eating\n", get_time()
			- philo->args->start_time, philo->id);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
		printf("%ld philosopher [%d] is sleeping\n", get_time()
			- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
		printf("%ld philosopher [%d] is thinking\n", get_time()
			- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	if (philo->args->philo_count % 2 != 0)
	{
		think_time = (philo->args->time_to_eat * 2)
			- philo->args->time_to_sleep;
		if (think_time > 0 && think_time < philo->args->time_to_die)
			ft_usleep(think_time, philo);
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		is_finished;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->args->print_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->args->print_mutex);
	if (philo->args->philo_count == 1)
		return (philo_think(philo), philo_take_forks(philo), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->args->time_to_eat, philo);
	pthread_mutex_lock(&philo->args->print_mutex);
	is_finished = philo->args->finished;
	pthread_mutex_unlock(&philo->args->print_mutex);
	while (is_finished == 0)
	{
		(philo_think(philo), philo_take_forks(philo));
		(philo_eat(philo), philo_sleep(philo));
		pthread_mutex_lock(&philo->args->print_mutex);
		is_finished = philo->args->finished;
		pthread_mutex_unlock(&philo->args->print_mutex);
	}
	return (NULL);
}
