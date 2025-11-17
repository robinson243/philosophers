#include "philo.h"

int	parse_input(t_table *table, char **av)
{
	table->philo_number = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	table->nbr_limit_meal = -1;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
	{
		printf("Use timestamps major than 60ms\n");
		return (-1);
	}
	if (table->time_to_die <= 0 || table->time_to_eat <= 0 
		|| table->time_to_sleep <= 0)
	{
		printf("Use positive numbers\n");
		return (-1);
	}
	if (av[5])
		table->nbr_limit_meal = ft_atol(av[5]);
	return (0);
}
