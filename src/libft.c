/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:12:41 by mmota             #+#    #+#             */
/*   Updated: 2022/03/10 01:00:44 by marmota          ###   ########.fr       */
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
