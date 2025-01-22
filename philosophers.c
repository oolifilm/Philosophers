/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:29:54 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/16 22:39:42 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_arg *args, t_philo *philo)
{
	pthread_mutex_lock(&(args->forks_mutex[philo->left]));
	print_status(args, philo->philosopher_id, "has taken a fork");
	if (args->num_of_philo != 1)
	{
		pthread_mutex_lock(&(args->forks_mutex[philo->right]));
		print_status(args, philo->philosopher_id, "has taken a fork");
		print_status(args, philo->philosopher_id, "is eating");
		pthread_mutex_lock(&(args->time_mutex));
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&(args->time_mutex));
		philo->meals_eaten_count++;
		waiting((long long)args->time_to_eat, args);
		pthread_mutex_unlock(&(args->forks_mutex[philo->right]));
	}
	pthread_mutex_unlock(&(args->forks_mutex[philo->left]));
	return (0);
}

static void	philo_lifespan(t_arg *args, t_philo *philo)
{
	if (args->num_of_philo - 1 == philo->philosopher_id
		&& philo->meals_eaten_count == 0)
		usleep(1);
	eating(args, philo);
	if (args->num_of_philo == 1)
		waiting((long long)args->time_to_sleep, args);
}

void	*routine(void *argv)
{
	t_arg	*args;
	t_philo	*philo;

	philo = (t_philo *)argv;
	args = philo->args;
	if (philo->philosopher_id % 2 == 0)
		thinking(args);
	while (!check_simulation_end(args))
	{
		philo_lifespan(args, philo);
		if (args->required_meals == philo->meals_eaten_count)
		{
			args->completed_meals_count++;
			break ;
		}
		print_status(args, philo->philosopher_id, "is sleeping");
		waiting((long long)args->time_to_sleep, args);
		print_status(args, philo->philosopher_id, "is thinking");
	}
	return (0);
}

int	print_status(t_arg *args, int philosopher_id, char *msg)
{
	long long	cur_time;

	pthread_mutex_lock(&(args->output_mutex));
	cur_time = get_time();
	if (cur_time < 0)
		return (-1);
	if (!check_simulation_end(args))
		printf("%lld %d %s\n", cur_time - args->simulation_start_time,
			philosopher_id, msg);
	if (str_compare_n(msg, "died", 4) == 0)
		return (0);
	pthread_mutex_unlock(&(args->output_mutex));
	return (0);
}

void	monitoring(t_arg *args, t_philo *philo)
{
	int			i;
	long long	cur_time;

	while (!check_simulation_end(args))
	{
		if ((args->required_meals != 0)
			&& (args->num_of_philo == args->completed_meals_count))
			lock_and_unlock_end_mutex(args);
		i = 0;
		while (i < args->num_of_philo)
		{
			cur_time = get_time();
			if ((cur_time - philo[i].last_meal_time) >= (args->time_to_die))
			{
				print_status(args, i, "died");
				lock_and_unlock_end_mutex(args);
				pthread_mutex_unlock(&(args->output_mutex));
			}
			i++;
		}
	}
}
