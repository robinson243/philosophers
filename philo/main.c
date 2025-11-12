/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:13:50 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 16:44:47 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac != 5)
	{
		printf("Error wrong number of arguments !\n");
		return (0);
	}
	if (!ft_numeric(av[1]) || !ft_numeric(av[2]) || !ft_numeric(av[3])
		|| !ft_numeric(av[4]))
	{
		printf("Some arguments are not digits\n");
		return (0);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoll(av[2]) <= 0 || ft_atoll(av[3]) <= 0
		|| ft_atoll(av[4]) <= 0)
	{
		printf("Some arguments are negative\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (check_args(ac, av) == 0)
		return (0);
	if (!init_everything(&table, av))
		return (1);
	if (!start_simulation(&table))
		return (1);
	return (0);
}
