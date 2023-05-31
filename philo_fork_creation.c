/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:38:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/31 15:51:18 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_philocreate(int argc, char **argv)
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
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].target_eats = -1;
		if (argc == 6)
			philo[i].target_eats = ft_atoi(argv[5]);
		philo[i].number_eats = 0;
		philo[i].last_eat = 0;
		philo[i].total_philo = ft_atoi(argv[1]);
		philo[i].actions = ft_action_create();
		i++;
	}
	return (philo);
}

t_fork	*ft_fork(int f)
{
	t_fork	*fork;
	int		i;

	i = 0;
	fork = malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	fork->fork = malloc(sizeof(int) * f);
	if (fork->fork == NULL)
		return (NULL);
	fork->mutex = malloc(sizeof(pthread_mutex_t) * f);
	if (fork->mutex == NULL)
		return (NULL);
	while (i < f)
	{
		fork->fork[i] = 0;
		pthread_mutex_init(&fork->mutex[i], NULL);
		i++;
	}
	return (fork);
}

t_action	*ft_action_create(void)
{
	t_action	*actions;
	int			i;

	actions = malloc(sizeof(t_action) * 5);
	if (!actions)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		actions[i].active = 0;
		actions[i].written = 0;
		i++;
	}
	actions[0].txt = "has taken a fork";
	actions[1].txt = "has taken a fork";
	actions[2].txt = "is eating";
	actions[3].txt = "is sleeping";
	actions[4].txt = "is thiking";
	return (actions);
}
