/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:09:54 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/16 22:39:56 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_arg *args)
{
	int	idx;

	if (pthread_mutex_init(&(args->output_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(args->time_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(args->simulation_end_mutex), NULL))
		return (1);
	args->forks_mutex = malloc(sizeof(pthread_mutex_t) * args->num_of_philo);
	if (!args->forks_mutex)
		return (1);
	idx = 0;
	while (idx < args->num_of_philo)
	{
		if (pthread_mutex_init(&args->forks_mutex[idx], NULL))
			return (1);
		idx++;
	}
	return (0);
}

int	init_args(t_arg *args, int ac, char **av)
{
	args->num_of_philo = str_to_int(av[1]);
	args->time_to_die = str_to_int(av[2]);
	args->time_to_eat = str_to_int(av[3]);
	args->time_to_sleep = str_to_int(av[4]);
	args->simulation_start_time = get_time();
	if (args->num_of_philo <= 0 || args->time_to_die < 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0
		|| args->simulation_start_time < 0)
		return (1);
	if (ac == 6)
	{
		args->required_meals = str_to_int(av[5]);
		if (args->required_meals <= 0)
			return (1);
		if (args->num_of_philo == 1)
			args->required_meals = 0;
	}
	if (init_mutex(args))
	{
		free(args->forks_mutex);
		return (1);
	}
	return (0);
}

int	init_philo(t_philo **philo, t_arg *args)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * args->num_of_philo);
	if (!(*philo))
		return (1);
	while (i < args->num_of_philo)
	{
		(*philo)[i].args = args;
		(*philo)[i].philosopher_id = i;
		(*philo)[i].left = i;
		if (i == args->num_of_philo - 1)
			(*philo)[i].right = 0;
		else
			(*philo)[i].right = i + 1;
		(*philo)[i].last_meal_time = get_time();
		(*philo)[i].meals_eaten_count = 0;
		i++;
	}
	return (0);
}

int	create_philo_thread(t_arg *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->num_of_philo)
	{
		philo[i].last_meal_time = get_time();
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (1);
		i++;
	}
	monitoring(args, philo);
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}
