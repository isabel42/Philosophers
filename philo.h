/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:09:05 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/26 17:35:18 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

enum act {righ_fork, left_fork, eating, sleeping, thinking};

typedef	struct s_action
{
	char	*txt;
	int		active;
	int		written;
}				t_action;

typedef struct s_philo {
	int		id;
	long	birth;
	long	death;
	long	time_to_die;	
	long	time_to_eat;
	int		time_to_sleep;
	int		target_eats;
	long	last_eat;
	int		number_eats;
	int		right_fork;
	int		right_fork_written;
	int		left_fork;
	int		left_fork_written;
	int		is_eating_written;
	int		is_sleeping;
	int		is_sleeping_written;
	int		is_thinking;
	int		is_thinking_written;
	t_action	*actions;
	int			total_philo;
}				t_philo;

typedef struct s_fork {
	int *fork;
	pthread_mutex_t *mutex;
}				t_fork;

typedef struct s_philofork {
	t_philo	*philo;
	t_fork	*fork;
}				t_philofork;

int	ft_atoi(const char *str);
void ft_my_usleep(int time);
void print_stamp(char *mess, t_philo philo);
long my_gettime_ms();
int ft_getmineats(t_philo *philo);
t_action	*ft_action_create();

#endif