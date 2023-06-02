/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:23:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/02 12:31:24 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_action_reset(t_philo *philo)
{
	int	j;

	j = 0;
	while (j < 5)
	{
		philo->actions[j].active = 0;
		philo->actions[j].written = 0;
		j++;
	}
}

void	ft_eat(t_philo *philo)
{
	long	time;

	time = my_gettime_ms();
	if (philo->id < philo->total_philo - 1 || philo->total_philo > 1)
	{
		philo->actions[1].active = 1;
		philo->last_eat = time - philo->birth;
		philo->number_eats++;
	}
	philo->actions[2].active = 1;
	while (philo->time_to_eat + time > my_gettime_ms())
		usleep(500);
}

void	ft_lock_mutex(pthread_mutex_t *mutex, t_philo *philo)
{
	if (pthread_mutex_lock(&mutex[philo->id]) != 0)
		return ;
	ft_action_reset(philo);
	if (philo->total_philo == 1)
		philo->actions[0].active = 1;
	if (philo->id == philo->total_philo - 1)
		{
			if (pthread_mutex_lock(&mutex[0]) != 0)
				return ;
		}
	else
	{
		if (pthread_mutex_lock(&mutex[philo->id + 1]) != 0)
			return ;
	}	
	philo->actions[0].active = 1;
}

void	ft_unlock_mutex(pthread_mutex_t *mutex, t_philo *philo)
{
	if (pthread_mutex_unlock(&mutex[philo->id]) != 0)
		return ;
	if (philo->id == philo->total_philo - 1)
	{
		if (pthread_mutex_unlock(&mutex[0]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_unlock(&mutex[philo->id + 1]) != 0)
			return ;
	}	
}

void	*routine(void *philo_fork)
{
	pthread_mutex_t	*mutex;
	t_philo			*philo;
	t_philofork		*philo_fork_new;
	long			time;

	philo_fork_new = (t_philofork *) philo_fork;
	philo = philo_fork_new->philo;
	mutex = philo_fork_new->mutex;
	while (42)
	{
		ft_lock_mutex(mutex, philo);
		ft_eat(philo);
		ft_unlock_mutex(mutex, philo);
		philo->actions[3].active = 1;
		time = my_gettime_ms();
		while (philo->time_to_sleep + time > my_gettime_ms())
			usleep(500);
		philo->actions[4].active = 1;
	}
	return (NULL);
}
