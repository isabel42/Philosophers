/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/22 17:32:02 by itovar-n         ###   ########.fr       */
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

void* routine(void *fork)
{
	t_fork	*j;
	j = (t_fork *)fork;
	printf("Test from thread %d\n",j[1].fork);
	return(NULL);
}

t_philo *ft_philocreate(int p, t_fork *fork)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * p);
	if (!philo)
		return (NULL);
	while(i < p)
	{
		philo[i].id = i;
		pthread_create(&philo[i].thread, NULL, &routine, fork);
		philo[i].last_eat = 20;
		i++;

	}
	return(philo);
}

t_fork	*ft_fork(int f)
{
	t_fork	*fork;
	int		i;

	i = 0;
	fork = malloc(sizeof(t_fork) * f);
	if (fork == NULL)
		return (NULL);
	while (i < f)
	{
		fork[i].fork = i;
		pthread_mutex_init(&fork[i].mutex, NULL);
		i++;
	}
	return(fork);
}

int main( int argc, char **argv)
{
	(void ) argc;
	t_philo *philo;
	int		i;
	t_fork	*fork;
	
	i = 0;
	fork = ft_fork(ft_atoi(argv[1]));
	if(fork == NULL)
		return(0);
	philo = ft_philocreate(ft_atoi(argv[1]), fork);
	if(philo == NULL)
		return(0);

	while(i < ft_atoi(argv[1]))
	{
		pthread_join(philo[i].thread , NULL);
		i++;
	}
	return (0);
}