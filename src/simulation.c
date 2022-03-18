/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:32:17 by mmota             #+#    #+#             */
/*   Updated: 2022/03/18 01:21:34 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&sim->end);
	if (!sim->dead )
	{
		pthread_mutex_lock(&sim->write);
		printf("%li %i is thinking\n", (get_time() - sim->start), philo->id);
		pthread_mutex_unlock(&sim->write);
	}
	else 
	{
		pthread_mutex_unlock(&sim->end);
		return (0);
	}
	pthread_mutex_unlock(&sim->end);
	return (1);

}

int	sleeping(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&sim->end);
	if (!sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_lock(&sim->write);
		printf("%li %i is sleeping\n", (get_time() - sim->start), philo->id);
		pthread_mutex_unlock(&sim->write);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_usleep(sim->specs.time_to_sleep);
		return (1);
	}
	pthread_mutex_unlock(&sim->end);
	return (0);
}

int	eating(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&sim->end);
	if (!sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_lock(&sim->write);
		printf("%li %i is eating\n", (get_time() - sim->start), philo->id);
		pthread_mutex_unlock(&sim->write);
		pthread_mutex_lock(&sim->time_meal);
		if (--philo->meals_count == 0)
			sim->finish_eat++;
		philo->time_meal = get_time();
		pthread_mutex_unlock(&sim->time_meal);
		if (get_time() - philo->time_meal - sim->specs.time_to_eat < sim->specs.time_to_die)
		{
			ft_usleep(sim->specs.time_to_eat);
			return (1);
		}
	}
	pthread_mutex_unlock(&sim->end);
	return (0);
}

int	get_forks(t_sim *sim, t_philos *philo)
{
	if (pthread_mutex_lock(&philo->left_fork) == 0)
	{
		pthread_mutex_lock(&sim->write);
		printf("%li %i has taken a fork\n", get_time() - sim->start, philo->id);
		pthread_mutex_unlock(&sim->write);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&sim->write);
		printf("%li %i has taken a fork\n", get_time() - sim->start, philo->id);
		pthread_mutex_unlock(&sim->write);
		return (1);
	}
	return (0);
}

void	*action(void *arg)
{
	static int	i = -1;
	t_sim		*sim;
	t_philos	*philo;

	sim = (t_sim *)arg;
	pthread_mutex_lock(&sim->increment);
	philo = &sim->philos[++i];
	pthread_mutex_unlock(&sim->increment);
	if (sim->specs.n_of_philos == 1)
	{
		ft_usleep(sim->specs.time_to_die);
		return (0);
	}
	if (philo->id % 2 != 0)
		ft_usleep(sim->specs.time_to_die / 10);
	while (1)
	{
		if (!get_forks(sim, philo))
			break;
		if (!eating(sim, philo))
			break;
		if (!sleeping(sim, philo))
			break;
		if (!thinking(sim, philo))
			break;
	}
	return (0);
}

void	*monitor(void *arg)
{
	static int	i = 0;
	t_sim		*sim;
	t_philos	*philo;

	sim = (t_sim *)arg;
	while (1)
	{
		pthread_mutex_lock(&sim->increment);
		philo = &sim->philos[i];
		pthread_mutex_unlock(&sim->increment);
		if (!death(sim, philo))
		{
			pthread_mutex_lock(&sim->increment);
			if (++i == sim->specs.n_of_philos)
				i = 0;
			pthread_mutex_unlock(&sim->increment);
		}
		else
			break ;
	}
	return (0);
}
