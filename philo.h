/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:41:09 by leaugust          #+#    #+#             */
/*   Updated: 2025/01/16 21:33:10 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*==================== header =====================*/
# include <memory.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*==================== structs =====================*/

typedef struct s_arg
{
	int				num_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				required_meals;
	int				simulation_end_flag;
	int				completed_meals_count;
	long long		simulation_start_time;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	simulation_end_mutex;
}					t_arg;

typedef struct s_philo
{
	t_arg			*args;
	pthread_t		thread_id;
	int				philosopher_id;
	int				left;
	int				right;
	long long		last_meal_time;
	int				meals_eaten_count;
}					t_philo;

int					str_compare_n(char *s1, char *s2, int n);
int					str_to_int(char *str);
long long			get_time(void);
void				ft_usleep(int ms);
void				thinking(t_arg *args);
void				waiting(long long wait_time, t_arg *args);

int					check_simulation_end(t_arg *args);
void				lock_and_unlock_end_mutex(t_arg *args);

int					init_mutex(t_arg *args);
int					init_args(t_arg *args, int ac, char **av);
int					init_philo(t_philo **philo, t_arg *args);

int					create_philo_thread(t_arg *args, t_philo *philo);
int					eating(t_arg *args, t_philo *philo);
void				*routine(void *argv);
int					print_status(t_arg *args, int philosopher_id, char *msg);
void				monitoring(t_arg *args, t_philo *philo);

void				destroy_all_mutex(t_arg *args);

#endif