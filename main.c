/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:04:59 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/16 16:44:24 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_arg *args)
{
	int	i;

	pthread_mutex_destroy(&(args->output_mutex));
	pthread_mutex_destroy(&(args->time_mutex));
	pthread_mutex_destroy(&(args->simulation_end_mutex));
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_mutex_destroy(&args->forks_mutex[i]);
		i++;
	}
	free(args->forks_mutex);
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (printf("Invalid argument number\n"), 1);
	memset(&args, 0, sizeof(t_arg));
	if (init_args(&args, ac, av) == 1)
		return (printf("Fail init struct or the error occeurs in argv"), 1);
	if (init_philo(&philo, &args) == 1)
	{
		printf("Fail init philo struct\n");
		destroy_all_mutex(&args);
		return (1);
	}
	if (create_philo_thread(&args, philo) == 1)
	{
		printf("Fail to run philo\n");
		destroy_all_mutex(&args);
		free(philo);
		return (1);
	}
	destroy_all_mutex(&args);
	free(philo);
	return (0);
}
