/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:20:42 by romukena          #+#    #+#             */
/*   Updated: 2025/11/11 17:36:38 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

t_philo *init_everything(t_table *table, char **av)
{
    int i;
    t_philo *philos;

	i = 0;
    init_table(table, av);

    init_forks_mutex(table);  
    init_mutex(table);        

    philos = init_tab_philo(table, table->len_philo);
    if (!philos)
        return NULL;
    table->start_sim = get_time();
	while (i < table->len_philo)
	{
		philos[i].last_meal = table->start_sim;
		i++;
	}
    return philos;
}

