/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/02 11:43:52 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stamp(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < philo[0].total_philo)
	{
		j = 0;
		while (j < 5)
		{
			if (philo[i].actions[j].active == 1
				&& philo[i].actions[j].written == 0)
			{
				philo[i].actions[j].written = 1;
				print_stamp(philo[i].actions[j].txt, philo[i]);
			}
			j++;
		}
		i++;
	}
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
		printf("\nAll philosophers have eaten at least %d times\n",
			philo[0].target_eats);
		return (1);
	}
	return (0);
}

int	ft_check_death(t_philo *philo, pthread_t *thread)
{
	int		i;
	long	time_death;

	i = 0;
	while (i < philo[0].total_philo)
	{
		if (my_gettime_ms() - philo[i].last_eat
			- philo[i].birth >= philo[i].time_to_die)
		{
			time_death = my_gettime_ms() - philo[i].birth;
			printf("\n%ld %d has died\n", time_death, i);
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

void	ft_check_exit(t_philo *philo, pthread_t *thread)
{
	while (42)
	{
		ft_stamp(philo);
		if (ft_check_meals(philo, thread) == 1)
			break ;
		if (ft_check_death(philo, thread) == 1)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_t		*thread;
	t_philofork		**philo_fork;

	if (ft_check_arg(argc, argv) == 0)
		return (0);
	mutex = ft_mutex(ft_atoi(argv[1]));
	if (mutex == NULL)
		return (0);
	philo = ft_philocreate(argc, argv);
	if (philo == NULL || philo->actions == NULL)
		return (0);
	thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (thread == NULL)
		return (0);
	philo_fork = malloc(sizeof(*philo_fork) * ft_atoi(argv[1]));
	if (philo_fork == NULL)
		return (0);
	if (ft_thread(philo, mutex, thread, philo_fork) == 0)
		return (0);
	ft_check_exit(philo, thread);
	pthread_mutex_destroy(mutex);
	ft_free_all(philo, mutex, thread, philo_fork);
	return (0);
}
