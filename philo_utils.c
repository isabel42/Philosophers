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


int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = sign * (-1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

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
	long	time;

	time = my_gettime_ms();
	printf("%ld %d %s\n",  time - philo.birth ,philo.id, mess);
}

long my_gettime_ms()
{
	long	time;
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return(time);
}

int ft_getmineats(t_philo *philo)
{
	int	i;
	int	min;

	i = 0;
	min = philo[0].number_eats;
	while(i < philo[0].total_philo)
	{
		if(philo[i].number_eats < min)
			min = philo[i].number_eats;
		i++;
	}
	return (min);
}

