/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:37:07 by romukena          #+#    #+#             */
/*   Updated: 2025/11/29 14:22:06 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	determine_fork_order(philo, &first, &second);
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
	{
		printf("%ld philosopher [%d] has taken a fork\n", get_time()
			- philo->args->start_time, philo->id);
		printf("%ld philosopher [%d] has taken a fork\n", get_time()
			- philo->args->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
		printf("%ld philosopher [%d] is thinking\n", get_time()
			- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	philo->last_meal = get_time();
	if (!philo->args->finished)
	{
		printf("%ld philosopher [%d] is eating\n", get_time()
			- philo->args->start_time, philo->id);
		philo->eat_count++;
	}
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	if (!philo->args->finished)
	{
		printf("%ld philosopher [%d] is sleeping\n", get_time()
			- philo->args->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_sleep, philo);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		is_finished;

	philo = (t_philo *)arg;
	if (init_philo_life(philo))
		return (NULL);
	stagger_start(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->args->print_mutex);
		is_finished = philo->args->finished;
		pthread_mutex_unlock(&philo->args->print_mutex);
		if (is_finished)
			break ;
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
