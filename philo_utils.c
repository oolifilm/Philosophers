/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:55:04 by leaugust          #+#    #+#             */
/*   Updated: 2024/12/17 16:55:19 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring_fini_mutex(t_arg *arg)
{
	pthread_mutex_lock(&(arg->fini_mutex));
	if (arg->finish == 1)
	{
		pthread_mutex_unlock(&(arg->fini_mutex));
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(arg->fini_mutex));
		return (0);
	}
}

void	pthread_mutex_lock_and_unlock(t_arg *arg)
{
	pthread_mutex_lock(&(arg->fini_mutex));
	arg->finish = 1;
	pthread_mutex_unlock(&(arg->fini_mutex));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}
