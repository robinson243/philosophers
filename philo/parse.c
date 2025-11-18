/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:42:47 by romukena          #+#    #+#             */
/*   Updated: 2025/11/18 15:42:48 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstrfd("Usage: ./philo nb_philo time_die\n", 2);
		ft_putstrfd(" time_eat time_sleep [nb_meals]\n", 2);
		return (1);
	}
	args->philo_count = ft_atol(argv[1]);
	args->time_to_die = ft_atol(argv[2]);
	args->time_to_eat = ft_atol(argv[3]);
	args->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		args->must_eat = ft_atol(argv[5]);
	else
		args->must_eat = -1;
	if (args->philo_count == -1 || args->time_to_die == -1
		|| args->time_to_eat == -1 || args->time_to_sleep == -1 || (argc == 6
			&& args->must_eat == -1))
		return (ft_putstrfd("Error: Invalid arguments\n", 2), 1);
	if (args->philo_count == 0)
		return (ft_putstrfd("Error: Need at least 1 philosopher\n", 2), 1);
	args->finished = 0;
	return (0);
}
