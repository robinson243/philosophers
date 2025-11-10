/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/10 12:27:11 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		philo_id;
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	int				alive;
}					t_philo;

typedef struct s_table
{
	int				len_philo;
	long long		start_sim;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				time_to_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}					t_table;

#endif