/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:12:56 by mmota             #+#    #+#             */
/*   Updated: 2022/04/05 21:23:22 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_death(char *argv[])
{
	long int	start;

	start = get_time();
	ft_usleep(ft_atoi(argv[2]));
	printf("%li %i died\n", get_time() - start, 1);
}

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
	t_sim	*sim;

	error_handling(argc, argv);
	if (ft_atoi(argv[1]) == 1)
	{
		one_philo_death(argv);
		return (0);
	}
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		exit_error(sim, "sim allocation failed");
	init_sim(sim, argc, argv);
	if (init_threads(sim))
		monitor(sim);
	free_structs(sim);
	return (0);
}
