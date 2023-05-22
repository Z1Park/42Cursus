/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:34:00 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/22 10:57:02 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define SLEEP_TICK 100

typedef struct s_philo
{
	pthread_t		pthread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_cnt_mutex;
	int				philo_num;
	long long		last_eat;
	long long		eat_count;
	long long		must_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	long long		philo_cnt;
	pthread_mutex_t	print;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks_mutex;
	int				*forks;
	int				stop;
	int				die_print;
	struct timeval	start_time;
	t_philo			*philos;
}	t_args;

typedef enum e_print
{
	PRINT_TAKE_FORK,
	PRINT_EATING,
	PRINT_SLEEPING,
	PRINT_THINKING,
	PRINT_DIED,
}	t_print;

long long	get_curr_time(t_args *args);
long long	print_message(t_args *args, long long philo_num, t_print prt);
int			philo_died(t_philo *philo);
void		stop_mutex(t_args *args);
int			is_stop(t_args *args);

t_args		*parse_arguments(int ac, char **av);

int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);

int			philo_init(t_args *args);
int			philo_start(t_args *args);
void		monitoring(t_args *args);

int			fork_lock(t_philo *philo, t_args *args);
int			fork_unlock(t_philo *philo, t_args *args);

#endif
