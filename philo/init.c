/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:13:50 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 12:32:12 by romukena         ###   ########.fr       */
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
	int		i;

	i = 0;
	tab = malloc(sizeof(t_philo) * n);
	if (!tab)
		return (NULL);
	while (i < n)
	{
		tab[i].id = i + 1;
		tab[i].left_fork = i;
		tab[i].right_fork = (i + 1) % n;
		tab[i].last_meal = main->start_sim;
		tab[i].table = main;
		i++;
	}
	return (tab);
}

pthread_mutex_t	*init_fork(int n)
{
	pthread_mutex_t	*tab;

	tab = malloc(sizeof(pthread_mutex_t) * n);
	if (!tab)
		return (NULL);
	return (tab);
}

int	init_mutex(t_table *main)
{
	if (pthread_mutex_init(&main->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&main->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&main->print_lock);
		return (0);
	}
	return (1);
}

int	init_forks_mutex(t_table *main)
{
	int	i;

	main->forks = init_fork(main->len_philo);
	if (!main->forks)
		return (0);
	i = 0;
	while (i < main->len_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL) != 0)
		{
			destroy_all_mutex(main);
			return (0);
		}
		i++;
	}
	return (1);
}
