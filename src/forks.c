/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:38:47 by mmota             #+#    #+#             */
/*   Updated: 2022/04/09 23:04:26 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_sim *sim, t_philos *philo)
{
	long int	current_time;

	pthread_mutex_lock(&sim->write);
	current_time = get_time() - sim->start;
	printf("%li %i has taken a fork\n", current_time, philo->id);
	pthread_mutex_unlock(&sim->write);
}

int	get_rightfork(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&sim->end);
	if (sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&sim->end);
	take_fork(sim, philo);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&sim->end);
	if (!sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		take_fork(sim, philo);
		return (1);
	}
	pthread_mutex_unlock(&sim->end);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	get_leftfork(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&sim->end);
	if (sim->dead)
	{
		philo->dead = 1;
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	pthread_mutex_unlock(&sim->end);
	take_fork(sim, philo);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&sim->end);
	if (!sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		take_fork(sim, philo);
		ft_usleep(1);
		return (1);
	}
	philo->dead = 1;
	pthread_mutex_unlock(&sim->end);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

int	get_forks(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&sim->end);
	if (sim->dead)
	{
		philo->dead = 1;
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&sim->end);
	if (!is_dying(sim, philo, sim->specs.time_to_eat * 1000))
	{
		if (philo->id % 2 == 0)
			if (get_leftfork(sim, philo))
				return (1);
		if (philo->id % 2 != 0)
			if (get_rightfork(sim, philo))
				return (1);
	}
	philo->dead = 1;
	return (0);
}
