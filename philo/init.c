/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:13:50 by romukena          #+#    #+#             */
/*   Updated: 2025/11/11 17:06:19 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *main, char **av)
{
	main->len_philo = ft_atoi(av[1]);
	main->time_to_die = ft_atoi(av[2]);
	main->time_to_eat = ft_atoi(av[3]);
	main->time_to_sleep = ft_atoi(av[4]);
	main->start_sim = 0;
	main->someone_died = 0;
}

t_philo	*init_tab_philo(t_table *main, int n)
{
	t_philo	*tab;
	int	i;
	
	i = 0;
	tab = malloc(sizeof(t_philo) * n);
	if (!tab)
		return (NULL);
	while (i < n)
	{
		tab[i].id = i + 1;
		tab[i].left_fork = i;
		tab[i].right_fork = (i + 1) % n;
		tab[i].last_meal = 0;
		tab[i].table = main;
		i++; 
	}
	return (tab);
}

pthread_mutex_t *init_fork(int n)
{
	pthread_mutex_t *tab;

	tab = malloc(sizeof(pthread_mutex_t) * n);
	if (!tab)
		return (NULL);
	return (tab);
}

void	destroy_all_mutex(t_table *main)
{
	int	i = 0;
	while (i < main->len_philo)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&main->print_lock);
	pthread_mutex_destroy(&main->death_lock);
	free(main->forks);
}

void	init_mutex(t_table *main)
{
	if (pthread_mutex_init(&main->print_lock, NULL) != 0)
		return ;
	if (pthread_mutex_init(&main->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&main->print_lock);
		return ;
	}
}


void	init_forks_mutex(t_table *main)
{
	int	i;

	main->forks = init_fork(main->len_philo);
	if (!main->forks)
		return ;
	i = 0;
	while (i < main->len_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL) != 0)
		{
			destroy_all_mutex(main);
			return ;
		}
		i++;
	}
}
