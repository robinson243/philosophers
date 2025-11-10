/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:13:50 by romukena          #+#    #+#             */
/*   Updated: 2025/11/10 13:30:00 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5)
	{
		if (ft_atoi(av[1]) < 0 || ft_atoll(av[2]) < 0 || ft_atoll(av[3]) < 0  || ft_atoll(av[4]) < 0)
		{
			printf("Some arguments is negatif\n");
			return (0);
		}
		
	}
	else
		printf("Error wrong number of arguments !\n");
	return (0);
}
