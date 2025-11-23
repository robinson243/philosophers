/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:44:56 by romukena          #+#    #+#             */
/*   Updated: 2025/11/23 20:23:37 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_args *args, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * args->philo_count);
	if (!*philos)
		return (1);
	while (i < args->philo_count)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_meal = get_time();
		(*philos)[i].finished = 0;
		(*philos)[i].args = args;
		(*philos)[i].left_fork = &args->forks[i];
		(*philos)[i].right_fork = &args->forks[(i + 1) % args->philo_count];
		i++;
	}
	return (0);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	actual;
	int		is_finished;

	actual = get_time();
	while ((get_time() - actual) < time)
	{
		pthread_mutex_lock(&philo->args->print_mutex);
		is_finished = philo->args->finished;
		pthread_mutex_unlock(&philo->args->print_mutex);
		if (is_finished == 1)
			break ;
		usleep(100);
	}
}

void	lock_forks_in_order(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	pthread_mutex_lock(*first);
}
