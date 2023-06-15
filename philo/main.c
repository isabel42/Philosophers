/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 13:39:25 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

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
	philo = ft_philocreate(argv, info->mul_mutex);
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
