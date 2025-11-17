#include "philo.h"

int main(int ac, char **av)
{
	t_table table;
	if (ac == 5 || ac == 6)
	{
		if (parse_input(&table, av) == -1)
			return (-1);
		// data_init(&table);
		// dinner_start(&table);
		// clean(&table);
	}
	else
	{
		printf("Wrong input\nCorrect is ./philo 5 800 200 200\n");
		return (2);
	}
	return (0);
}
