/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:08:28 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/05 19:42:40 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_death(int i, t_philo *philo,
	pthread_t *thread, pthread_mutex_t mutex_death)
{
	long	time;

	time = my_gettime_ms();
	if (pthread_mutex_lock(&mutex_death) != 0)
		return (0);
	if (i == -1)
	{
		if (ft_check_death(philo, thread) == 1)
		{
			if (pthread_mutex_unlock(&mutex_death) != 0)
				return (0);
			return (1);
		}
		else
		{
			if (pthread_mutex_unlock(&mutex_death) != 0)
				return (0);
			return (0);
		}
	}
	else //if (philo->time_to_die > time - philo->last_eat)
		philo->last_eat = time - philo->birth;
	if (pthread_mutex_unlock(&mutex_death) != 0)
		return (0);
	return (0);
}

int	ft_eat_total(int i, t_philo *philo,
	pthread_t *thread, pthread_mutex_t mutex_total_eats)
{
	if (pthread_mutex_lock(&mutex_total_eats) != 0)
		return (0);
	if (i == -1)
	{
		if (ft_check_meals(philo, thread) == 1)
			return (1);
		else
			return (0);
	}
	else
	{
		philo[0].number_eats++;
		return (0);
	}
	if (pthread_mutex_unlock(&mutex_total_eats) != 0)
		return (0);
}

int	ft_check_death(t_philo *philo, pthread_t *thread)
{
	int		i;

	i = 0;
	while (i < philo[0].total_philo)
	{
		if (my_gettime_ms() - philo[i].last_eat
			- philo[i].birth >= philo[i].time_to_die)
		{
			i = 0;
			while (i < philo[0].total_philo)
			{
				pthread_detach(thread[i]);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_meals(t_philo *philo, pthread_t *thread)
{
	int	i;

	if (ft_getmineats(philo) == philo[0].target_eats)
	{
		i = 0;
		while (i < philo[0].total_philo)
		{
			pthread_detach(thread[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
