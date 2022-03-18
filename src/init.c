/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:32:30 by mmota             #+#    #+#             */
/*   Updated: 2022/03/18 16:18:28 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sim(t_sim *sim, int argc, char *argv[])
{
	init_specs(sim, argc, argv);
	pthread_mutex_init(&sim->increment, NULL);
	pthread_mutex_init(&sim->write, NULL);
	pthread_mutex_init(&sim->time_meal, NULL);
	pthread_mutex_init(&sim->end, NULL);
	sim->dead = 0;
	sim->finish_eat = 0;
	sim->start = get_time();
	init_philos(sim, sim->start);
	init_forks(sim);
	return (1);
}

void	init_specs(t_sim *sim, int argc, char *argv[])
{
	sim->specs.n_of_philos = ft_atoi(argv[1]);
	sim->specs.time_to_die = ft_atoi(argv[2]);
	sim->specs.time_to_eat = ft_atoi(argv[3]);
	sim->specs.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->specs.n_times_philos_must_eat = ft_atoi(argv[5]);
	else
		sim->specs.n_times_philos_must_eat = -1;
}

void	init_philos(t_sim *sim, long int start)
{
	int			i;

	sim->philos = malloc(sizeof(t_philos) * sim->specs.n_of_philos);
	if (!sim->philos)
		exit_error(sim, "philos allocation failed");
	i = -1;
	while (++i < sim->specs.n_of_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_count = sim->specs.n_times_philos_must_eat;
		sim->philos[i].time_meal = start;
	}
}

void	init_forks(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->specs.n_of_philos)
	{
		if (pthread_mutex_init(&sim->philos[i].left_fork, NULL) == 0)
		{
			if (sim->specs.n_of_philos == 1)
			{
				sim->philos[0].right_fork = NULL;
				return ;
			}
			else if (i != 0)
				sim->philos[i].right_fork = &sim->philos[i - 1].left_fork;
		}
		else
			exit_error(sim, "could'n initiate forks");
	}
	sim->philos[0].right_fork = &sim->philos[sim->specs.n_of_philos - 1].left_fork;
}

int	init_threads(t_sim *sim)
{
	int	i;

	sim->threads = (pthread_t *)malloc(sizeof(pthread_t) * sim->specs.n_of_philos);
	if (!sim->threads)
		exit_error(sim, "threads allocation failed");
	i = -1;
	while (++i < sim->specs.n_of_philos)
	{
		if (pthread_create(&sim->threads[i], NULL, &action, sim) != 0)
			exit_error(sim, "Thread creation failed\n");
	}
	return (1);
}
