/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:38:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/02 09:59:34 by itovar-n         ###   ########.fr       */
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

pthread_mutex_t	*ft_mutex(int f)
{
	pthread_mutex_t	*mutex;
	int		i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * f);
	if (mutex == NULL)
		return (NULL);
	while (i < f)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
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

int	ft_thread(t_philo *philo, pthread_mutex_t *mutex,
	pthread_t *thread, t_philofork	**philo_fork)
{
	int			i;

	i = 0;
	while (i < philo[0].total_philo)
	{
		philo_fork[i] = malloc(sizeof(t_philofork));
		if (philo_fork == NULL)
			return (0);
		philo_fork[i]->mutex = mutex;
		philo_fork[i]->philo = &philo[i];
		pthread_create(&thread[i], NULL, &routine, philo_fork[i]);
		i++;
	}
	return (1);
}
