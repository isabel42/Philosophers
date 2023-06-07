/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:08:28 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/07 17:02:25 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_total(int i, t_philo *philo, t_info *info)
{
	int	res;

	res = 0;
	if (pthread_mutex_lock(&info->mul_mutex->mutex_total_eats) != 0)
		return (0);
	if (i == -1)
	{
		if (ft_getmineats(philo, info) == info->target_eats)
		{
			res = 1;
			info->stop = 1;
		}
	}
	else
		philo[0].number_eats++;
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_total_eats) != 0)
		return (0);
	return (res);
}

int	ft_death_time_change(int i, int res, t_philo *philo, t_info *info)
{
	int	j;

	j = 0;
	if (i == -1)
	{
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
	}
	else
		philo->last_eat = my_gettime_ms() - philo->birth;
	return (res);
}

int	ft_death_time(int i, t_philo *philo, t_info *info)
{
	int		res;

	res = -1;
	if (pthread_mutex_lock(&info->mul_mutex->mutex_death) != 0)
		return (0);
	res = ft_death_time_change(i, res, philo, info);
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_death) != 0)
		return (0);
	return (res);
}
