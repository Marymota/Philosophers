/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:12:41 by mmota             #+#    #+#             */
/*   Updated: 2022/03/22 16:44:47 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *n)
{
	int				sign;
	unsigned int	res;

	res = 0;
	sign = 1;
	while (*n == '-' || *n == '+')
	{
		if (*n == '-')
			sign = -1;
		++n;
	}
	while (*n)
	{
		if (!ft_isdigit(*n))
			return (-1);
		res = res * 10 + *n - '0';
		++n;
	}
	if (res <= 2147483648)
		return (res * sign);
	if (res >= 2147483648 && sign > 0)
		return (-1);
	return (0);
}

long int	get_time(void)
{
	long int		ms;
	struct timeval	time;

	ms = 0;
	if (gettimeofday(&time, NULL) != 0)
	{
		perror("Can't get current time");
		exit(EXIT_FAILURE);
	}
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(long int time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
