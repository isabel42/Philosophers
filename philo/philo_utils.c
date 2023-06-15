/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:06:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 10:26:34 by itovar-n         ###   ########.fr       */
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

void	print_stamp(char *mess, t_philo philo)
{
	long	time;

	time = my_gettime_ms();
	printf("%ld ms: Philo %d %s\n", time - philo.birth, philo.id, mess);
}

int	my_gettime_ms(void)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (int) current_time.tv_sec * 1000 + (int) current_time.tv_usec / 1000;
	return (time);
}

void	ft_write(int i, t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(&info->mul_mutex->mutex_write) != 0)
		return ;
	if (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop) && i >= 0 && i < 5)
		print_stamp(info->actions[i], *philo);
	else if (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop) && i == -1)
	{
		ft_update(&info->stop, 1, &info->mul_mutex->mutex_stop);
		printf("\nAll philosophers have eaten at least %d times\n",
			info->target_eats);
	}
	else if (!ft_stop_check(&info->stop, &info->mul_mutex->mutex_stop) && i == 5)
	{
		ft_update(&info->stop, 1, &info->mul_mutex->mutex_stop);
		printf("\n");
		print_stamp(info->actions[i], *philo);
	}
	if (pthread_mutex_unlock(&info->mul_mutex->mutex_write) != 0)
		return ;
}
