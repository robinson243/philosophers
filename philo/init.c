/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:13:50 by romukena          #+#    #+#             */
/*   Updated: 2025/11/10 18:05:40 by romukena         ###   ########.fr       */
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
}

t_philo	*init_tab_philo(int n)
{
	t_philo	*tab;
	
	tab = malloc(sizeof(t_philo) * n);
	if (!tab)
		return (NULL);
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