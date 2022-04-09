/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:32:35 by mmota             #+#    #+#             */
/*   Updated: 2022/04/09 23:06:05 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_sim *sim, int i)
{
	while (!death(sim, &sim->philos[i]) && !end_meals(sim))
	{
		if (++i == sim->specs.n_philos)
			i = 0;
	}
	i = -1;
	while (++i == sim->specs.n_philos)
		sim->philos[i].dead = 1;
	ft_usleep(1);
	i = -1;
	while (++i < sim->specs.n_philos - 1)
	{
		pthread_mutex_destroy(sim->philos[i].right_fork);
	}
	i = -1;
	while (++i < sim->specs.n_philos)
	{
		if (pthread_join(sim->threads[i], NULL) != 0)
			exit_error(sim, "Thread join failed\n");
	}
	pthread_mutex_destroy(&sim->write);
	pthread_mutex_destroy(&sim->increment);
	pthread_mutex_destroy(&sim->time_meal);
	pthread_mutex_destroy(&sim->end);
	pthread_mutex_destroy(&sim->philos[0].left_fork);
}

int	end_meals(t_sim *sim)
{
	if (sim->finish_eat >= sim->specs.n_philos && !sim->dead)
	{
		pthread_mutex_lock(&sim->end);
		sim->dead = 1;
		pthread_mutex_lock(&sim->write);
		printf("All philos are full!\n");
		pthread_mutex_unlock(&sim->write);
		pthread_mutex_unlock(&sim->end);
		return (1);
	}
	return (0);
}

int	death(t_sim *sim, t_philos *philo)
{
	long int	curr_time;
	long int	death_time;

	pthread_mutex_lock(&sim->end);
	pthread_mutex_lock(&sim->time_meal);
	curr_time = get_time() - sim->start;
	death_time = curr_time - philo->time_meal;
	if (death_time >= sim->specs.time_to_die)
	{
		pthread_mutex_unlock(&sim->time_meal);
		sim->dead = 1;
		printf("%li %i died\n", curr_time, philo->id);
		ft_usleep(1000);
		pthread_mutex_unlock(&sim->end);
		return (1);
	}
	pthread_mutex_unlock(&sim->time_meal);
	pthread_mutex_unlock(&sim->end);
	return (0);
}

int	is_dying(t_sim *sim, t_philos *philo, long int time)
{
	long int	current_time;

	current_time = get_time() - sim->start;
	if (time - current_time > 0)
		return (0);
	philo->dead = 1;
	ft_usleep(10);
	return (1);
}

void	free_structs(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->specs.n_philos)
	{
		sim->threads[i] = 0;
		++i;
	}
	if (sim->philos)
		free(sim->philos);
	if (sim->threads)
		free(sim->threads);
	if (sim)
		free(sim);
}
