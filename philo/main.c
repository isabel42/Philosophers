/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/05 13:09:00 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_exit(t_philo *philo, pthread_t *thread, t_mulmutex *mul_mutex)
{
	while (42)
	{
		if (ft_eat_total(-1, philo, thread, mul_mutex->mutex_total_eats) == 1)
			break ;
		if (ft_eat_death(-1, philo, thread, mul_mutex->mutex_death) == 1)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_mulmutex		*mul_mutex;
	pthread_t		*thread;
	t_philomutex	**philo_mutex;

	if (ft_check_arg(argc, argv) == 0)
		return (0);
	mul_mutex = ft_mutex(ft_atoi(argv[1]));
	if (mul_mutex == NULL)
		return (0);
	philo = ft_philocreate(argc, argv);
	if (philo == NULL || philo->actions == NULL)
		return (0);
	thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (thread == NULL)
		return (0);
	philo_mutex = malloc(sizeof(*philo_mutex) * ft_atoi(argv[1]));
	if (philo_mutex == NULL)
		return (0);
	if (ft_thread(philo, mul_mutex, thread, philo_mutex) == 0)
		return (0);
	ft_check_exit(philo, thread, mul_mutex);
	ft_free_all(philo, mul_mutex, thread, philo_mutex);
	return (0);
}
