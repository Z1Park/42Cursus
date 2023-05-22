/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:34:00 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/28 11:53:08 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define SLEEP_TICK 100
# define SEM_PRINT "sem_print"
# define SEM_FORKS "sem_forks"

typedef struct s_philo
{
	pthread_t		pthread;
	long long		philo_num;
	sem_t			*sem_die_check;
	long long		last_eat;
	long long		eat_count;
}	t_philo;

typedef struct s_args
{
	long long		philo_cnt;
	sem_t			*print;
	sem_t			*forks;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		must_eat;
	struct timeval	start_time;
	t_philo			*philo;
	pid_t			*pids;
}	t_args;

typedef enum e_print
{
	PRINT_TAKE_FORK,
	PRINT_EATING,
	PRINT_SLEEPING,
	PRINT_THINKING,
	PRINT_DIED,
}	t_print;

long long	get_cur_time(t_args *args);
long long	print_message(t_args *args, long long philo_num, t_print prt);
char		*ft_itoa(int n);

t_args		*parse_arguments(int ac, char **av);

int			eating(t_args *args);
int			sleeping(t_args *args);
int			thinking(t_args *args);

int			philo_init(t_args *args);
pid_t		philo_start(t_args *args);
void		monitoring(t_args *args, pid_t pid);

#endif
