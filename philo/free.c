/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 13:46:03 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philo *philo, t_info *info,
			t_philoinfo **philo_info, pthread_t *thread)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->mul_mutex->mutex_death);
	pthread_mutex_destroy(&info->mul_mutex->mutex_write);
	pthread_mutex_destroy(&info->mul_mutex->mutex_stop);
	free(thread);
	while (i < info->total_philo)
	{
		pthread_mutex_destroy(philo[i].mutex_local);
		pthread_mutex_destroy(&info->mul_mutex->mutex_fork[i]);
		free(philo_info[i]);
		i++;
	}
	free(philo->mutex_local);
	free(philo);
	free(info->mul_mutex->mutex_fork);
	free(info->mul_mutex);
	free(philo_info);
	free(info->actions);
	free(info);
}
