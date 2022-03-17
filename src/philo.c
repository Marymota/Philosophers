/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:12:56 by mmota             #+#    #+#             */
/*   Updated: 2022/03/17 18:34:07 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handling(int argc, char *argv[])
{
	if ((argc < 5 && argc != 6))
	{
		printf("not enough arguments\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 6)
	{
		printf("too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[1]) > 200)
	{
		printf("invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[2]) < 0.60 || ft_atoi(argv[3]) < 0.60)
	{
		printf("invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[4]) < 0)
	{
		printf("invalid arguments\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	t_sim *sim;

	error_handling(argc, argv);
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		exit_error(sim, "sim allocation failed");
	init_sim(sim, argc, argv);
	init_threads(sim);
	if (pthread_join(*sim->monitor, NULL) != 0)
		exit_error(sim, "monitor join failed\n");
	usleep(100);
	free_structs(sim);
	return (0);
}
