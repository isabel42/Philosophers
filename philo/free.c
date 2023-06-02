/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/02 10:01:03 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philo *philo, pthread_mutex_t *mutex,
			pthread_t *thread, t_philofork **philo_fork)
{
	int	i;

	i = 0;
	free(mutex);
	free(thread);
	while (i < philo[0].total_philo)
	{
		free(philo_fork[i]);
		free(philo[i].actions);
		i++;
	}
	free(philo_fork);
	free(philo);
}
