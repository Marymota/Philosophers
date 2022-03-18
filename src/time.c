/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:13:14 by mmota             #+#    #+#             */
/*   Updated: 2022/03/17 23:15:00 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
