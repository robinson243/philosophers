/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/17 17:33:14 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_args {
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	int		finished;
	long	start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}	t_args;

typedef struct s_philo {
	int		id;
	int		eat_count;
	long	last_meal;
	pthread_t	thread_id;
	t_args		*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int		finished;
}	t_philo;


// utils
long	get_time(void);
void	ft_usleep(long time);
void	ft_putstrfd(char *str, int fd);
long ft_atol(const char *str);

int	parse_args(int argc, char **argv, t_args *args);

// life
void	*philo_life(void *philo_void);

// init & clean
int		init_simulation(int argc, char **argv, t_args *args, t_philo **philos);
void	clean_simulation(t_args *args, t_philo *philos);

// error
int		error(char *msg);

void	destroy_all_mutexes(pthread_mutex_t *tab, int i);
int	init_mutexes(t_args *args);

#endif
