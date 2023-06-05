/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:23:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/05 13:47:11 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(int i, t_philo *philo, pthread_mutex_t mutex_write)
{
	if (pthread_mutex_lock(&mutex_write) != 0)
		return ;
	print_stamp(philo->actions[i].txt, *philo);
	if (pthread_mutex_unlock(&mutex_write) != 0)
		return ;
}

void	ft_eat(t_philo *philo, t_mulmutex *mul_mutex)
{
	long	time;

	time = my_gettime_ms();
	if (philo->id < philo->total_philo - 1 || philo->total_philo > 1)
	{
		ft_eat_death(0, philo, NULL, mul_mutex->mutex_death);
		ft_eat_total(0, philo, NULL, mul_mutex->mutex_total_eats);
		ft_write(1, philo, mul_mutex->mutex_write);
	}
	ft_write(2, philo, mul_mutex->mutex_write);
	while (philo->time_to_eat + time > my_gettime_ms())
		usleep(500);
}

void	ft_lock_mutex(t_mulmutex *mul_mutex, t_philo *philo)
{
	if (pthread_mutex_lock(&mul_mutex->mutex_fork[philo->id]) != 0)
		return ;
	if (philo->total_philo == 1)
	{
		ft_write(0, philo, mul_mutex->mutex_write);
	}
	if (philo->id == philo->total_philo - 1)
	{
		if (pthread_mutex_lock(&mul_mutex->mutex_fork[0]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_lock(&mul_mutex->mutex_fork[philo->id + 1]) != 0)
			return ;
	}	
	ft_write(0, philo, mul_mutex->mutex_write);
}

void	ft_unlock_mutex(t_mulmutex *mul_mutex, t_philo *philo)
{
	if (pthread_mutex_unlock(&mul_mutex->mutex_fork[philo->id]) != 0)
		return ;
	if (philo->id == philo->total_philo - 1)
	{
		if (pthread_mutex_unlock(&mul_mutex->mutex_fork[0]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_unlock(&mul_mutex->mutex_fork[philo->id + 1]) != 0)
			return ;
	}	
}

void	*routine(void *philo_mutex)
{
	t_mulmutex		*mul_mutex;
	t_philo			*philo;
	t_philomutex	*philo_mutex_new;
	long			time;

	philo_mutex_new = (t_philomutex *) philo_mutex;
	philo = philo_mutex_new->philo;
	mul_mutex = philo_mutex_new->mul_mutex;
	while (42)
	{
		ft_lock_mutex(mul_mutex, philo);
		ft_eat(philo, mul_mutex);
		ft_unlock_mutex(mul_mutex, philo);
		ft_write(3, philo, mul_mutex->mutex_write);
		time = my_gettime_ms();
		while (philo->time_to_sleep + time > my_gettime_ms())
			usleep(500);
		ft_write(4, philo, mul_mutex->mutex_write);
	}
	return (NULL);
}
