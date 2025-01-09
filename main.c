/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:04:59 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/07 22:55:13 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	distroy_all_mutex(t_arg *arg)
{
	int	i;

	pthread_mutex_destroy(&(arg->print));
	pthread_mutex_destroy(&(arg->time));
	pthread_mutex_destroy(&(arg->fini_mutex));
	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_mutex_destroy(&arg->fork[i]);
		i++;
	}
	free(arg->fork);
}

int	main(int ac, char **av)
{
	t_arg arg;
	t_philo *philo;

	if (ac != 5 && ac != 6)
		return (printf("Invalid argument number\n"), 1);
	memset(&arg, 0, sizeof(t_arg));
	if (init_args_element(&arg, ac, av) == 1)
		return (printf("Fail init struct or the error occeurs in argv"), 1);
	if (init_philo(&philo, &arg) == 1)
		return (printf("Fail init philo struct"), 1);
	if (create_philo_thread(&arg, philo) == 1)
		return (printf("Fail to run philo"), 1);
	distroy_all_mutex(&arg);
	free(philo);
	return (0);
}
