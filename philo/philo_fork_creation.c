/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:38:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 14:42:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*ft_info(int argc, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->target_eats = -1;
	if (argc == 6)
		info->target_eats = ft_atoi(argv[5]);
	info->total_philo = ft_atoi(argv[1]);
	info->actions = ft_action_create();
	info->stop = 0;
	info->mul_mutex = ft_mutex(ft_atoi(argv[1]));
	return (info);
}

t_philo	*ft_philocreate(char **argv, t_mulmutex *mul_mutex)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (NULL);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i;
		philo[i].birth = my_gettime_ms();
		philo[i].number_eats = 0;
		philo[i].last_eat = 0;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].left_fork = &mul_mutex->mutex_fork[i];
		philo[i].right_fork = &mul_mutex->mutex_fork[(i + 1)
			% ft_atoi(argv[1])];
		philo[i].total_philo = ft_atoi(argv[1]);
		philo[i].mutex_local = &mul_mutex->mutex_local[i];
		i++;
	}
	return (philo);
}

t_mulmutex	*ft_mutex(int f)
{
	t_mulmutex	*mul_mutex;
	int			i;

	i = 0;
	mul_mutex = malloc(sizeof(t_mulmutex));
	if (mul_mutex == NULL)
		return (NULL);
	mul_mutex->mutex_fork = malloc(sizeof(t_mulmutex) * f);
	if (mul_mutex->mutex_fork == NULL)
		return (NULL);
	mul_mutex->mutex_local = malloc(sizeof(pthread_mutex_t) * f);
	if (mul_mutex->mutex_local == NULL)
		return (NULL);
	while (i < f)
	{
		pthread_mutex_init(&mul_mutex->mutex_fork[i], NULL);
		pthread_mutex_init(&mul_mutex->mutex_local[i], NULL);
		i++;
	}
	pthread_mutex_init(&mul_mutex->mutex_write, NULL);
	pthread_mutex_init(&mul_mutex->mutex_death, NULL);
	pthread_mutex_init(&mul_mutex->mutex_stop, NULL);
	return (mul_mutex);
}

char	**ft_action_create(void)
{
	char	**actions;

	actions = malloc(sizeof(char *) * 6);
	if (!actions)
		return (NULL);
	actions[0] = "has taken left fork";
	actions[1] = "has taken right fork";
	actions[2] = "is eating";
	actions[3] = "is sleeping";
	actions[4] = "is thiking";
	actions[5] = "died";
	return (actions);
}

int	ft_thread(t_philo *philo, t_info *info,
	pthread_t *thread, t_philoinfo **philo_info)
{
	int			i;

	i = 0;
	while (i < info->total_philo)
	{
		philo_info[i] = malloc(sizeof(t_philoinfo));
		if (philo_info == NULL)
			return (0);
		philo_info[i]->info = info;
		philo_info[i]->philo = &philo[i];
		if (pthread_create(&thread[i], NULL, &routine, philo_info[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
