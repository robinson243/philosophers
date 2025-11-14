/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:36:34 by romukena          #+#    #+#             */
/*   Updated: 2025/11/14 16:36:54 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) *1000 + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long long	end;
	long long	left;

	end = get_time() + ms;
	while (get_time() < end)
	{
		left = end - get_time();
		if (left > 10)
			usleep(5000);
		else if (left > 1)
			usleep(100);
		else
			continue ;
	}
}
