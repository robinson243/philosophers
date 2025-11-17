/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/17 13:00:25 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "limits.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;

}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	long				full;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_number;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meal;
	long				start_sim;
	bool				end_sim;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

/* Utils */

int						valid_input(long number);
int						ft_ispace(char c);
long					ft_atol(const char *str);

int	parse_input(t_table *table, char **av);

#endif