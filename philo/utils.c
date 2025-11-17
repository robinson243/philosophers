#include "philo.h"

int ft_ispace(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int	valid_input(long number)
{
	if (number < 0)
		return (-1);
	if (number > INT_MAX)
		return (-1);
	return (0);
}

long ft_atol(const char *str)
{
	int	i;
	long	res;
	int minus;

	i = 0;
	res = 0;
	minus = 1;
	while (ft_ispace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] != '\0')
		return (-1);
	res *= minus;
	if (valid_input(res) == -1)
		return (-1);
	return (res);
}
