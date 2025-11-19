/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:44:38 by romukena          #+#    #+#             */
/*   Updated: 2025/11/19 03:07:39 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putstrfd(char *str, int fd)
{
	int		i;
	ssize_t	ret;

	i = 0;
	while (str[i])
		i++;
	ret = write(fd, str, i);
	(void)ret;
}

static int	ft_ispace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	valid_input(long number)
{
	if (number < 0)
		return (-1);
	if (number > INT_MAX)
		return (-1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		minus;

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
