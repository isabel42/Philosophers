/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:23:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 10:29:55 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_stop_check(int *stop, pthread_mutex_t *mutex_stop)
{
	int	res;

	if (pthread_mutex_lock(mutex_stop))
		return (-1);
	res = *stop;
	if (pthread_mutex_unlock(mutex_stop))
		return (-1);
	return (res);
}

int	ft_update(int *numb_eats, int new_numb_eats, pthread_mutex_t *mutex_local)
{
	if (pthread_mutex_lock(mutex_local))
		return (-1);
	*numb_eats = new_numb_eats;
	if (pthread_mutex_unlock(mutex_local))
		return (-1);
	return (0);
}

void	my_usleep(int waiting_time, t_info *info)
{
	int	ac_time;

	ac_time = my_gettime_ms();
	while (waiting_time + ac_time > my_gettime_ms()
			&& !ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
		usleep(500);
	return ;
}

int	ft_get_tot_philo(t_philo *philo)
{
	int	cp_total_philo;

	pthread_mutex_lock(philo->mutex_local);
	cp_total_philo = philo->total_philo;
	pthread_mutex_unlock(philo->mutex_local);
	return (cp_total_philo);
}

int	ft_eat(t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (-1);
	ft_write(0, philo, info);
	if (ft_get_tot_philo(philo) == 1)
	{
		while (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
			usleep(500);
		if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (-1);
	}
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (-1);
	ft_write(1, philo, info);
	ft_write(2, philo, info);
	ft_update(&philo->number_eats, philo->number_eats + 1, philo->mutex_local);
	ft_update(&philo->last_eat, my_gettime_ms() - philo->birth, philo->mutex_local);
	my_usleep(philo->time_to_eat, info);
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (-1);
	return(0);
}

void	*routine(void *philo_info)
{
	t_info			*info;
	t_philo			*philo;
	t_philoinfo		*philo_info_new;

	philo_info_new = (t_philoinfo *) philo_info;
	philo = philo_info_new->philo;
	info = philo_info_new->info;
	if (philo->id % 2)
		usleep(500);
	if (info->total_philo > 100 && philo->id % 4)
		usleep(500);
	while (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
	{
		if (ft_eat(philo, info) == -1)
			return (NULL);
		ft_write(3, philo, info);
		my_usleep(philo->time_to_eat, info);
		ft_write(4, philo, info);
	}	
	return (NULL);
}
