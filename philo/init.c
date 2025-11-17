#include "philo.h"




int	data_init(t_table *table)
{
	table->end_sim = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table)
		return (-1);
	
	return (0);
}