/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 17:28:42 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		philo_id;
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				len_philo;
	long long		start_sim;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				someone_died;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}					t_table;

int					init_everything(t_table *table, char **av);
void				init_table(t_table *table, char **av);
void				destroy_all_mutex(t_table *table);
int					init_forks_mutex(t_table *table);
int					init_mutex(t_table *table);
pthread_mutex_t		*init_fork(int n);
t_philo				*init_tab_philo(t_table *table, int n);
void				cleanup(t_table *table);
int					check_args(int ac, char **av);
int					start_simulation(t_table *table);
void				*philosopher_routine(void *arg);
int					create_philosophers_threads(t_table *table);
void				*monitor_routine(void *arg);
long long			get_time(void);
void				ft_usleep(long ms);
void				print_status(t_philo *philo, char *status);
int					ft_atoi(const char *str);
long long			ft_atoll(const char *str);
int					ft_numeric(char *str);

#endif