/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:08:28 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/13 17:35:15 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_total(t_philo *philo, t_info *info)
{
	int	res;

	if (pthread_mutex_lock(&info->mul_mutex->mutex_total_eats) != 0)
		return (0);
	res = 0;
	if (ft_getmineats(philo, info) == info->target_eats)
	{
		res = 1;
		if (pthread_mutex_lock(&info->mul_mutex->mutex_stop) != 0)
				return (0);
		info->stop = 1;
		if (pthread_mutex_unlock(&info->mul_mutex->mutex_stop) != 0)
				return (0);
	}
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_total_eats) != 0)
		return (0);
	return (res);
}

int	ft_death_time(t_philo *philo, t_info *info)
{
	int	res;
	int	j;

	res = -1;
	if (pthread_mutex_lock(&info->mul_mutex->mutex_death) != 0)
		return (0);
	j = 0;
	while (j < info->total_philo)
	{
		if (my_gettime_ms() - philo[j].last_eat
			- philo[j].birth >= info->time_to_die)
		{
			res = j;
			info->stop = 1;
			break ;
		}
		j++;
	}
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_death) != 0)
		return (0);
	return (res);
}
