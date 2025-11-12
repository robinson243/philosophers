/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:13:50 by romukena          #+#    #+#             */
/*   Updated: 2025/11/12 12:35:24 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5)
	{
		if (!ft_numeric(av[1]) || !ft_numeric(av[2]) || !ft_numeric(av[3])
			|| !ft_numeric(av[4]))
		{
			printf("Some arguments are not digits\n");
			return (0);
		}
		if (ft_atoi(av[1]) <= 0 || ft_atoll(av[2]) <= 0 || ft_atoll(av[3]) <= 0
			|| ft_atoll(av[4]) <= 0)
		{
			printf("Some arguments are negatif\n");
			return (0);
		}
	}
	else
		printf("Error wrong number of arguments !\n");
	return (0);
}
