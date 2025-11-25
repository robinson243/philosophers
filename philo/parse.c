/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:42:47 by romukena          #+#    #+#             */
/*   Updated: 2025/11/25 02:57:09 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_limits(t_args *args, int argc)
{
	if (args->philo_count < 1 || args->philo_count > 200)
		return (ft_putstrfd("Error: philo_count must be 1-200\n", 2), 1);
	if (args->time_to_die < 60 || args->time_to_die > 10000)
		return (ft_putstrfd("Error: time_to_die must be 60-10000ms\n", 2), 1);
	if (args->time_to_eat < 60 || args->time_to_eat > 5000)
		return (ft_putstrfd("Error: time_to_eat must be 60-5000ms\n", 2), 1);
	if (args->time_to_sleep < 60 || args->time_to_sleep > 5000)
		return (ft_putstrfd("Error: time_to_sleep must be 60-5000ms\n", 2), 1);
	if (argc == 6 && (args->must_eat < 0 || args->must_eat > 10000))
		return (ft_putstrfd("Error: must_eat must be 0-10000\n", 2), 1);
	return (0);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstrfd("Usage: ./philo nb_philo time_die", 2);
		ft_putstrfd(" time_eat time_sleep[nb_meals]\n", 2);
	}
	args->philo_count = ft_atol(argv[1]);
	args->time_to_die = ft_atol(argv[2]);
	args->time_to_eat = ft_atol(argv[3]);
	args->time_to_sleep = ft_atol(argv[4]);
	args->must_eat = -1;
	if (argc == 6)
		args->must_eat = ft_atol(argv[5]);
	if (args->philo_count == -1 || args->time_to_die == -1
		|| args->time_to_eat == -1 || args->time_to_sleep == -1 || (argc == 6
			&& args->must_eat == -1))
		return (ft_putstrfd("Error: Invalid arguments\n", 2), 1);
	if (validate_limits(args, argc) == 1)
		return (1);
	args->finished = 0;
	return (0);
}
