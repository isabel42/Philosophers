/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:09:05 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/22 15:59:30 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_philo {
	int	id;
	pthread_t thread;
	int	last_eat;
}				t_philo;

typedef struct s_fork {
	int fork;
	pthread_mutex_t mutex;
}				t_fork;

#endif