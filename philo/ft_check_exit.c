/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:08:28 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 14:42:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

void	ft_cp_die_eat_birth(t_philo *philo,
			int *cp_time_to_die, int *cp_last_eat, int *cp_birth)
{
	pthread_mutex_lock(philo->mutex_local);
	*cp_time_to_die = philo->time_to_die;
	*cp_last_eat = philo->last_eat;
	*cp_birth = philo->birth;
	pthread_mutex_unlock(philo->mutex_local);
}

void	philo_die(t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(&info->mul_mutex->mutex_death))
		return ;
	ft_write(5, philo, info);
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_death))
		return ;
}

void	ft_get_min_eat(t_philo *philo, int *min_eat)
{
	pthread_mutex_lock(philo->mutex_local);
	if (philo->number_eats < *min_eat)
		*min_eat = philo->number_eats;
	pthread_mutex_unlock(philo->mutex_local);
}

void	ft_join(t_info *info, pthread_t *thread)
{
	int	a;

	a = 0;
	while (a < info->total_philo)
	{
		pthread_join(thread[a], NULL);
		a++;
	}
}

void	ft_check_exit(t_philo *philo, pthread_t *thread, t_info *info)
{
	int		i;
	int		cp_last_eat;
	int		cp_time_to_die;
	int		cp_birth;
	int		min_eat;

	while (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
	{
		i = 0;
		min_eat = INT_MAX;
		while (i < info->total_philo)
		{
			ft_cp_die_eat_birth(&philo[i],
				&cp_time_to_die, &cp_last_eat, &cp_birth);
			if (my_gettime_ms() - cp_last_eat - cp_birth >= cp_time_to_die)
				philo_die(&philo[i], info);
			ft_get_min_eat(&philo[i], &min_eat);
			i++;
		}
		if (min_eat >= info->target_eats && info->target_eats != -1)
			ft_write(-1, philo, info);
	}
	ft_join(info, thread);
}
