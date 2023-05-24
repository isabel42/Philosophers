/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/23 15:46:41 by itovar-n         ###   ########.fr       */
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


void* routine(void *philo_fork)
{
	t_fork	*fork;
	t_philo	philo;
	t_philofork philo_fork_new;
	struct timeval current_time;
	philo_fork_new = *(t_philofork *)philo_fork;
	philo = philo_fork_new.philo;
	fork = philo_fork_new.fork;
	for(int i = 0; i < 1; i++)
	{
		pthread_mutex_lock(&fork->mutex);
		gettimeofday(&current_time, NULL);
		fork->fork[philo.id] = 1;
		printf("%ld %d has taken a fork\n", current_time.tv_sec * 1000 + current_time.tv_usec / 1000  - philo.birth ,philo.id);
		if (philo.id < philo.total_philo - 1 || philo.total_philo > 1)
		{
			if (philo.total_philo > 1)
				fork->fork[philo.id + 1] = 1;
			else
				fork->fork[0] = 1;
			gettimeofday(&current_time, NULL);
			printf("%ld %d has taken a fork\n", current_time.tv_sec * 1000 + current_time.tv_usec / 1000  - philo.birth ,philo.id);
			gettimeofday(&current_time, NULL);
			printf("%ld %d is eating\n", current_time.tv_sec * 1000 + current_time.tv_usec / 1000  - philo.birth ,philo.id);
		}
		usleep(philo.time_to_eat * 1000);
		// fork->fork[philo.id] = 0;
		// if (philo.id < philo.total_philo - 1 || philo.total_philo > 1)
		// {
		// 	if (philo.total_philo > 1)
		// 		fork->fork[philo.id + 1] = 0;
		// 	else
		// 		fork->fork[0] = 0;
		// }
		pthread_mutex_unlock(&fork->mutex);
		gettimeofday(&current_time, NULL);
		printf("%ld %d is sleping\n", current_time.tv_sec * 1000 + current_time.tv_usec / 1000  - philo.birth ,philo.id);
		usleep(philo.time_to_sleep * 1000);
		gettimeofday(&current_time, NULL);
		printf("%ld %d is thinking\n", current_time.tv_sec * 1000 + current_time.tv_usec / 1000  - philo.birth ,philo.id);
	}
	return(NULL);
}

t_philo *ft_philocreate(int argc, char **argv)
{
	t_philo	*philo;
	struct timeval current_time;
	int		i;
	int		p;

	i = 0;
	p = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * p);
	if (!philo)
		return (NULL);
	gettimeofday(&current_time, NULL);
	while(i < p)
	{
		philo[i].id = i;
		philo[i].birth = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		philo[i].time_to_die = ft_atoi(argv[2]);	
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].target_eats = ft_atoi(argv[5]);
		else
			philo[i].target_eats = -1;
		philo[i].number_eats = 0;
		philo[i].last_eat = 0;
		philo[i].total_philo = ft_atoi(argv[1]);
		i++;

	}
	return(philo);
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
	while (i < f)
	{
		fork->fork[i] = 0;
		i++;
	}
	pthread_mutex_init(&fork->mutex, NULL);
	return(fork);
}

int main( int argc, char **argv)
{
	t_philo *philo;
	t_fork	*fork;
	pthread_t *thread;
	t_philofork *philo_fork;
	int		i;
	
	fork = ft_fork(ft_atoi(argv[1]));
	if(fork == NULL)
		return(0);
	philo = ft_philocreate(argc, argv);
	if (philo == NULL)
		return(0);
	thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (thread == NULL)
		return(0);
	i = 0;
	while(i < ft_atoi(argv[1]))
	{
		philo_fork = malloc(sizeof(t_philofork));
		if (philo_fork == NULL)
			return(0);
		philo_fork->fork = fork;
		philo_fork->philo = philo[i];
		pthread_create(&thread[i], NULL, &routine, philo_fork);
		i++;
	}
	i = 0;
	while(i < ft_atoi(argv[1]))
	{
		pthread_join(thread[i] , NULL);
		i++;
	}
	return (0);
}