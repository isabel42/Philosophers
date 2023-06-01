/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:09:05 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/01 16:15:22 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

enum e_act {righ_fork, left_fork, eating, sleeping, thinking};

typedef struct s_action
{
	char	*txt;
	int		active;
	int		written;
}				t_action;

typedef struct s_philo {
	int			id;
	long		birth;
	long		death;
	long		time_to_die;	
	long		time_to_eat;
	long		time_to_sleep;
	int			target_eats;
	long		last_eat;
	int			number_eats;
	t_action	*actions;
	int			total_philo;
}				t_philo;

typedef struct s_fork {
	int				*fork;
	pthread_mutex_t	*mutex;
}				t_fork;

typedef struct s_philofork {
	t_philo	*philo;
	t_fork	*fork;
}				t_philofork;

// philo_utils.c
int			ft_atoi(const char *str);
int			ft_strlen(char *s);
void		print_stamp(char *mess, t_philo philo);
long		my_gettime_ms(void);
int			ft_getmineats(t_philo *philo);
void		ft_my_usleep(long time, long current_time);

// routine.c
void		ft_action_reset(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_lock_mutex(t_fork *fork, t_philo *philo);
void		ft_unlock_mutex(t_fork *fork, t_philo *philo);
void		*routine(void *philo_fork);

// philo_fork_creation.c 
t_philo		*ft_philocreate(int argc, char **argv);
t_fork		*ft_fork(int f);
t_action	*ft_action_create(void);
int			ft_thread(t_philo *philo, t_fork *fork,
				pthread_t *thread, t_philofork	**philo_fork);

// free.c
void		ft_free_all(t_philo *philo, t_fork *fork,
				pthread_t *thread, t_philofork **philo_fork);

// arg_check.c
int			ft_check_digit(int argc, char **argv);
int			ft_check_int(int argc, char **argv);
int			ft_check_arg(int argc, char **argv);

#endif