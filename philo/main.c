/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/14 22:17:48 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>


void	update_last_meal(t_philo *philo, int *ph_tt_die, int *last_meal)
{
	pthread_mutex_lock(philo->mutex_local);
	*ph_tt_die = philo->time_to_die;
	*last_meal = philo->last_eat;
	pthread_mutex_unlock(philo->mutex_local);
}

void	philo_die(t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(&info->mul_mutex->mutex_death))
		return ;
	ft_update(&info->stop, 1, &info->mul_mutex->mutex_stop);
	ft_write(5, philo, info);
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_death))
		return ;
}

void	check_philo_eat(t_philo *philo, int *min_eat)
{
	pthread_mutex_lock(philo->mutex_local);
	if (philo->number_eats < *min_eat)
		*min_eat = philo->number_eats;
	pthread_mutex_unlock(philo->mutex_local);
}

void	ft_check_exit(t_philo *philo, pthread_t *thread, t_info *info)
{
	int		a;
	int		i;
	int		last_meal;
	int		ph_tt_die;
	int		min_eat;

	while (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
	{
		i = -1;
		min_eat = INT_MAX;
		while (++i < philo[0].total_philo)
		{
			update_last_meal(&philo[i], &ph_tt_die, &last_meal);
			if (my_gettime_ms() - last_meal >= ph_tt_die)
				philo_die(&philo[i], info);
			check_philo_eat(&philo[i], &min_eat);
		}
		if (min_eat >= info->target_eats && info->target_eats != -1)
		{
			ft_update(&info->stop, 1, &info->mul_mutex->mutex_stop);
			ft_write(-1, philo, info);
		}
	}
	a = 0;
	while (a < info->total_philo)
	{
		pthread_join(thread[a], NULL);
		a++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		*thread;
	t_info			*info;
	t_philoinfo		**philo_info;

	if (ft_check_arg(argc, argv) == 0)
		return (0);
	thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (thread == NULL)
		return (0);
	info = ft_info(argc, argv);
	if (!info || info->actions == NULL)
		return (0);
	philo = ft_philocreate(argv, info->mul_mutex->mutex_fork);
	if (philo == NULL)
		return (0);
	philo_info = malloc(sizeof(t_philoinfo *) * ft_atoi(argv[1]));
	if (!philo_info)
		return (0);
	if (ft_thread(philo, info, thread, philo_info) == 0)
		return (0);
	ft_check_exit(philo, thread, info);
	ft_free_all(philo, info, philo_info, thread);
	return (0);
}
