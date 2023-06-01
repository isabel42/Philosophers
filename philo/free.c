/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/31 17:45:41 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philo *philo, t_fork *fork,
			pthread_t *thread, t_philofork **philo_fork)
{
	int	i;

	i = 0;
	free(fork->fork);
	free(fork->mutex);
	free(fork);
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