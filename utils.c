/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:54:48 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/07 20:00:24 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 9223372036854775807 && sign == -1)
		return (-1);
	else if (res > 9223372036854775807)
		return (-1);
	return (sign * res);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	passing_time(long long wait_time, t_arg *arg)
{
	long long	start;
	long long	cur_time;

	start = get_time();
	while (!monitoring_fini_mutex(arg))
	{
		cur_time = get_time();
		if ((cur_time - start) >= wait_time)
			break ;
		usleep(100);
	}
}

void	time_thinking(t_arg *arg)
{
	struct timeval	get_time;
	struct timeval	time_stat;
	int				time_take;

	gettimeofday(&get_time, NULL);
	while (1)
	{
		gettimeofday(&time_stat, NULL);
		time_take = time_stat.tv_usec - get_time.tv_usec + (time_stat.tv_sec
				- get_time.tv_sec) * 1000000;
		if (time_take > arg->time_to_eat * 900)
			break ;
		ft_usleep(arg->time_to_eat);
	}
}
