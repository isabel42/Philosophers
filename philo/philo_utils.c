/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:06:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 16:28:01 by itovar-n         ###   ########.fr       */
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

int	print_stamp(char *mess, t_philo philo)
{
	long	time;

	time = my_gettime_ms();
	if (time == -1)
		return (-1);
	printf("%ld ms: Philo %d %s\n", time - philo.birth, philo.id, mess);
	return (0);
}

int	my_gettime_ms(void)
{
	int				time;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (int) current_time.tv_sec * 1000 + (int) current_time.tv_usec / 1000;
	return (time);
}

int	ft_write(int i, t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(&info->mul_mutex->mutex_write) != 0)
		return (-1);
	if (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
	{
		if (i >= 0 && i < 5)
		{
			if (print_stamp(info->actions[i], *philo) == -1)
				return (-1);
		}
		else if (ft_update(&info->stop, 1, &info->mul_mutex->mutex_stop) == -1)
			return (-1);
		if (i == -1)
		{
			printf("\nAll philosophers have eaten at least %d times\n",
				info->target_eats);
		}
		else if (i == 5)
		{
			if (print_stamp(info->actions[i], *philo) == -1)
				return (-1);
		}
	}
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_write) != 0)
		return (-1);
	return (0);
}

void	my_usleep(int waiting_time, t_info *info)
{
	int	ac_time;

	ac_time = my_gettime_ms();
	if (ac_time == -1)
		return ;
	while (waiting_time + ac_time > my_gettime_ms()
		&& !ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop))
		usleep(500);
	return ;
}
