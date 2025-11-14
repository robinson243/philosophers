/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:41:03 by romukena          #+#    #+#             */
/*   Updated: 2025/11/14 02:33:47 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long long	start;
	long long	now;
	long long	left;

	start = get_time();
	while (1)
	{
		now = get_time();
		if (now - start >= ms)
			break ;
		left = ms - (now - start);
		if (left > 2)
			usleep((left - 1) * 1000);
		else
			usleep(50);
	}
}

void	run_one_philo(t_philo *p)
{
	t_table		*t;
	long long	target;
	long long	now;

	t = p->table;
	pthread_mutex_lock(&t->forks[p->left_fork]);
	print_status(p, "has taken a fork");
	target = t->start_sim + t->time_to_die;
	now = get_time();
	if (target > now)
		ft_usleep(target - now);
	pthread_mutex_lock(&t->print_lock);
	if (t->someone_died == 0)
		printf("%lld philosophe[%d] is died\n", get_time() - t->start_sim,
			p->id);
	pthread_mutex_unlock(&t->print_lock);
	pthread_mutex_unlock(&t->forks[p->left_fork]);
	pthread_mutex_lock(&t->death_lock);
	t->someone_died = 1;
	pthread_mutex_unlock(&t->death_lock);
}

void	take_forks_ordered(t_philo *p)
{
	t_table	*t;
	int		a;
	int		b;

	t = p->table;
	a = p->left_fork;
	b = p->right_fork;
	if (b < a)
	{
		a = p->right_fork;
		b = p->left_fork;
	}
	pthread_mutex_lock(&t->forks[a]);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(&t->forks[b]);
	print_status(p, "has taken a fork");
}

void	drop_forks_ordered(t_philo *p)
{
	t_table	*t;
	int		a;
	int		b;

	t = p->table;
	a = p->left_fork;
	b = p->right_fork;
	if (b < a)
	{
		a = p->right_fork;
		b = p->left_fork;
	}
	pthread_mutex_unlock(&t->forks[b]);
	pthread_mutex_unlock(&t->forks[a]);
}

void	start_eating(t_philo *p)
{
	t_table	*t;

	t = p->table;
	pthread_mutex_lock(&t->death_lock);
	p->last_meal = get_time();
	pthread_mutex_unlock(&t->death_lock);
	print_status(p, "is eating");
	ft_usleep(t->time_to_eat);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)arg;
	t = p->table;
	if (p->id % 2 == 0)
		usleep(1000);
	if (t->len_philo == 1)
	{
		run_one_philo(p);
		return (NULL);
	}
	while (t->someone_died == 0)
	{
		take_forks_ordered(p);
		start_eating(p);
		drop_forks_ordered(p);
		if (t->someone_died)
			break ;
		print_status(p, "is sleeping");
		ft_usleep(t->time_to_sleep);
		print_status(p, "is thinking");
	}
	return (NULL);
}
