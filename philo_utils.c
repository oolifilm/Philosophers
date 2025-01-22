/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:55:04 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/16 21:32:36 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_end(t_arg *args)
{
	pthread_mutex_lock(&(args->simulation_end_mutex));
	if (args->simulation_end_flag == 1)
	{
		pthread_mutex_unlock(&(args->simulation_end_mutex));
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(args->simulation_end_mutex));
		return (0);
	}
}

void	lock_and_unlock_end_mutex(t_arg *args)
{
	pthread_mutex_lock(&(args->simulation_end_mutex));
	args->simulation_end_flag = 1;
	pthread_mutex_unlock(&(args->simulation_end_mutex));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}
