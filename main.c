/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/31 16:28:16 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_thread(t_philo *philo, t_fork *fork,
	pthread_t *thread, t_philofork	**philo_fork)
{
	int			i;

	i = 0;
	while (i < philo[0].total_philo)
	{
		philo_fork[i] = malloc(sizeof(t_philofork));
		if (philo_fork == NULL)
			return (0);
		philo_fork[i]->fork = fork;
		philo_fork[i]->philo = &philo[i];
		pthread_create(&thread[i], NULL, &routine, philo_fork[i]);
		i++;
	}
	return (1);
}

void	ft_check_exit(t_philo *philo, pthread_t *thread)
{
	int		a;
	long	time_death;
	int		i;
	int		j;

	while (42)
	{
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
			break ;
		}
		i = 0;
		while (i < philo[0].total_philo)
		{
			if (my_gettime_ms() - philo[i].last_eat
				- philo[i].birth > philo[i].time_to_die)
			{
				a = i;
				time_death = my_gettime_ms() - philo[i].birth;
				break ;
			}
			i++;
		}
		if (i < philo[0].total_philo)
		{
			i = 0;
			while (i < philo[0].total_philo)
			{
				pthread_detach(thread[i]);
				i++;
			}
			printf("\n");
			printf("%ld %d has died\n", time_death, a);
			break ;
		}
	}
}


int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_fork		*fork;
	pthread_t	*thread;
	t_philofork	**philo_fork;

	fork = ft_fork(ft_atoi(argv[1]));
	if (fork == NULL || fork->fork == NULL || fork->mutex == NULL)
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
	if (ft_thread(philo, fork, thread, philo_fork) == 0)
		return (0);
	ft_check_exit(philo, thread);
	return (0);
}
