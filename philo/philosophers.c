/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:37:07 by romukena          #+#    #+#             */
/*   Updated: 2025/11/29 14:18:33 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	determine_fork_order(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second)
{
    if (philo->id == philo->args->philo_count)
    {
        *first = philo->right_fork;
        *second = philo->left_fork;
    }
    else if (philo->id % 2 == 1)
    {
        *first = philo->left_fork;
        *second = philo->right_fork;
    }
    else
    {
        *first = philo->right_fork;
        *second = philo->left_fork;
    }
}

void    philo_take_forks(t_philo *philo)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;

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

int    init_philo_life(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->print_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->args->print_mutex);
    
    if (philo->args->philo_count == 1)
    {
        pthread_mutex_lock(&philo->args->print_mutex);
        printf("%ld philosopher [%d] has taken a fork\n", get_time()
            - philo->args->start_time, philo->id);
        pthread_mutex_unlock(&philo->args->print_mutex);
        ft_usleep(philo->args->time_to_die + 1, philo);
        return (1);
    }
    return (0);
}

void    stagger_start(t_philo *philo)
{
    if (philo->args->philo_count % 2 == 1)
    {
        if (philo->id % 2 == 0)
            usleep(0);
        else if (philo->id == philo->args->philo_count)
            usleep((philo->args->time_to_eat / 2) * 1000);
        else
            usleep(100);
    }
    else
    {
        if (philo->id % 2 == 0)
            usleep(1000);
    }
}

void    *philo_life(void *arg)
{
    t_philo *philo;
    int     is_finished;

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
