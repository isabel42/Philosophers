/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:23:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/07 16:04:07 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(int i, t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(&info->mul_mutex->mutex_write) != 0)
		return ;
	if (info->stop == 0 && i >= 0 && i < 5)
		print_stamp(info->actions[i], *philo);
	else if (info->stop == 1 && i == -1)
		printf("\nAll philosophers have eaten at least %d times\n",
			info->target_eats);
	else if ((info->stop == 1 && i == 5))
	{
		printf("\n");
		print_stamp(info->actions[i], *philo);
	}
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_write) != 0)
		return ;
}

void	ft_eat(t_philo *philo, t_info *info)
{
	long	time;

	time = my_gettime_ms();
	if (philo->id < info->total_philo - 1 || info->total_philo > 1)
	{
		ft_death_time(philo->id, philo, info);
		ft_write(1, philo, info);
	}
	ft_write(2, philo, info);
	ft_eat_total(philo->id, philo, info);
	while (info->time_to_eat + time > my_gettime_ms() && info->stop == 0)
		usleep(500);
}

void	ft_lock_mutex(t_info *info, t_philo *philo)
{
	if (pthread_mutex_lock(&info->mul_mutex->mutex_fork[philo->id]) != 0)
		return ;
	if (info->total_philo == 1)
		ft_write(0, philo, info);
	if (philo->id == info->total_philo - 1)
	{
		if (pthread_mutex_lock(&info->mul_mutex->mutex_fork[0]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_lock(&info->mul_mutex
				->mutex_fork[philo->id + 1]) != 0)
			return ;
	}
	ft_write(0, philo, info);
}

void	ft_unlock_mutex(t_info *info, t_philo *philo)
{
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_fork[philo->id]) != 0)
		return ;
	if (philo->id == info->total_philo - 1)
	{
		if (pthread_mutex_unlock(&info->mul_mutex->mutex_fork[0]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_unlock(&info->mul_mutex
				->mutex_fork[philo->id + 1]) != 0)
			return ;
	}	
}

void	*routine(void *philo_info)
{
	t_info			*info;
	t_philo			*philo;
	t_philoinfo		*philo_info_new;
	long			time;

	philo_info_new = (t_philoinfo *) philo_info;
	philo = philo_info_new->philo;
	info = philo_info_new->info;
	if (philo->id % 2)
		usleep(500);
	if (info->total_philo > 100 && philo->id % 4)
		usleep(500);
	while (info->stop == 0)
	{
		ft_lock_mutex(info, philo);
		ft_eat(philo, info);
		ft_unlock_mutex(info, philo);
		ft_write(3, philo, info);
		time = my_gettime_ms();
		while (info->time_to_sleep + time > my_gettime_ms() && info->stop == 0)
			usleep(500);
		ft_write(4, philo, info);
	}
	return (NULL);
}
