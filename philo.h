/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:09:05 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/23 15:22:07 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo {
	int	id;
	long birth;
	int	time_to_die;	
	int	time_to_eat;
	int	time_to_sleep;
	int	target_eats;
	int	last_eat;
	int	number_eats;
	int	total_philo;
}				t_philo;

typedef struct s_fork {
	int *fork;
	pthread_mutex_t mutex;
}				t_fork;

typedef struct s_philofork {
	t_philo	philo;
	t_fork	*fork;
}				t_philofork;

#endif