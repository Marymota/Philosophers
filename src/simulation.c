/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:32:17 by mmota             #+#    #+#             */
/*   Updated: 2022/04/09 17:00:36 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_meal(t_sim *sim, t_philos *philo)
{
	long int	current_time;

	pthread_mutex_lock(&sim->write);
	current_time = get_time() - sim->start;
	printf("%li %i is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&sim->write);
	pthread_mutex_lock(&sim->time_meal);
	philo->time_meal = current_time;
	if (--philo->meals_count == 0)
		sim->finish_eat++;
	pthread_mutex_unlock(&sim->time_meal);
}

int	thinking(t_sim *sim, t_philos *philo)
{
	long int	current_time;

	pthread_mutex_lock(&sim->end);
	if (!sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_lock(&sim->write);
		current_time = get_time() - sim->start;
		printf("%li %i is thinking\n", current_time, philo->id);
		pthread_mutex_unlock(&sim->write);
		ft_usleep(1);
		return (1);
	}
	pthread_mutex_unlock(&sim->end);
	return (0);
}

int	sleeping(t_sim *sim, t_philos *philo)
{
	long int	current_time;

	pthread_mutex_lock(&sim->end);
	if (sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&sim->end);
	pthread_mutex_lock(&sim->write);
	current_time = get_time() - sim->start;
	printf("%li %i is sleeping\n", current_time, philo->id);
	pthread_mutex_unlock(&sim->write);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_usleep(sim->specs.time_to_sleep);
	return (1);
}

int	eating(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&sim->end);
	if (!sim->dead)
	{
		pthread_mutex_unlock(&sim->end);
		get_meal(sim, philo);
		ft_usleep(sim->specs.time_to_eat);
		return (1);
	}
	pthread_mutex_unlock(&sim->end);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
	if (sim->specs.n_philos == 1)
		return (0);
	while (1)
	{
		if (philo->meals_count == 0 || !get_forks(sim, philo))
			break ;
		if (!eating(sim, philo))
			break ;
		if (!sleeping(sim, philo))
			break ;
		if (!thinking(sim, philo))
			break ;
	}
	ft_usleep(10);
	return (0);
}
