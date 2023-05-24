/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:06:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/24 15:13:39 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_my_usleep(int time)
{
	int	i;

	i = 0;
	while (i < time)
	{
		usleep(1);
		i++;
	}
}

void print_stamp(char *mess, t_philo philo)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("%ld %d %s\n", current_time.tv_sec * 1000 + current_time.tv_usec / 1000  - philo.birth ,philo.id, mess);
}

long my_gettime_ms()
{
	long	time;
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return(time);

}