/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:23:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/31 15:28:28 by itovar-n         ###   ########.fr       */
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
	if (philo->id < philo->total_philo - 1 || philo->total_philo > 1)
	{
		philo->actions[1].active = 1;
		philo->last_eat = my_gettime_ms() + philo->time_to_eat - philo->birth;
		philo->number_eats++;
	}
	philo->actions[2].active = 1;
	usleep(philo->time_to_eat * 1000);
}

void	ft_lock_mutex(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->mutex[philo->id]);
	ft_action_reset(philo);
	philo->actions[0].active = 1;
	if (philo->id == philo->total_philo - 1)
		pthread_mutex_lock(&fork->mutex[0]);
	else
		pthread_mutex_lock(&fork->mutex[philo->id + 1]);
}

void	ft_unlock_mutex(t_fork *fork, t_philo *philo)
{
	pthread_mutex_unlock(&fork->mutex[philo->id]);
	if (philo->id == philo->total_philo - 1)
		pthread_mutex_unlock(&fork->mutex[0]);
	else
		pthread_mutex_unlock(&fork->mutex[philo->id + 1]);
}

void	*routine(void *philo_fork)
{
	t_fork		*fork;
	t_philo		*philo;
	t_philofork	*philo_fork_new;

	philo_fork_new = (t_philofork *) philo_fork;
	philo = philo_fork_new->philo;
	fork = philo_fork_new->fork;
	while (42)
	{
		ft_lock_mutex(fork, philo);
		ft_eat(philo);
		ft_unlock_mutex(fork, philo);
		philo->actions[3].active = 1;
		usleep(philo->time_to_sleep * 1000);
		philo->actions[4].active = 1;
	}
	return (NULL);
}