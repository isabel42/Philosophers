/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/07 16:00:23 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philo *philo, t_info *info,
			t_philoinfo **philo_info, pthread_t *thread)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(info->mul_mutex->mutex_fork);
	pthread_mutex_destroy(&info->mul_mutex->mutex_death);
	pthread_mutex_destroy(&info->mul_mutex->mutex_total_eats);
	pthread_mutex_destroy(&info->mul_mutex->mutex_write);
	free(philo);
	free(thread);
	while (i < info->total_philo)
	{
		free(philo_info[i]);
		i++;
	}
	free(info->mul_mutex->mutex_fork);
	free(info->actions);
	free(info->mul_mutex);
	free(philo_info);
	free(info);
}
