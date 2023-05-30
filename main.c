/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:57:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/26 17:34:11 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *philo_fork)
{
	t_fork	*fork;
	t_philo	*philo;
	t_philofork *philo_fork_new;
	
	philo_fork_new = (t_philofork *) philo_fork;
	philo = philo_fork_new->philo;
	fork = philo_fork_new->fork;
	for(int i = 0; i < 42; i++)
	{
		pthread_mutex_lock(&fork->mutex[philo->id]);
		if(philo->id == philo->total_philo - 1)
			pthread_mutex_lock(&fork->mutex[0]);
		else
			pthread_mutex_lock(&fork->mutex[philo->id + 1]);
		philo->is_thinking = 0;
		philo->is_thinking_written = 0;
		philo->right_fork = 1;
		if (philo->id < philo->total_philo - 1 || philo->total_philo > 1)
		{
			philo->left_fork = 1;
			philo->last_eat = my_gettime_ms() + philo->time_to_eat - philo->birth;
			philo->number_eats ++;
		}
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&fork->mutex[philo->id]);
		if(philo->id == philo->total_philo - 1)
			pthread_mutex_unlock(&fork->mutex[0]);
		else
			pthread_mutex_unlock(&fork->mutex[philo->id + 1]);
		philo->left_fork = 0;
		philo->right_fork = 0;
		philo->left_fork_written = 0;
		philo->right_fork_written = 0;
		philo->is_eating_written = 0;
		philo->is_sleeping = 1;
		usleep(philo->time_to_sleep * 1000);
		philo->is_sleeping = 0;
		philo->is_sleeping_written = 0;
		philo->is_thinking = 1;
	}
	return(NULL);
}

t_philo *ft_philocreate(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (NULL);
	while(i < ft_atoi(argv[1]))
	{
		philo[i].id = i;
		philo[i].birth = my_gettime_ms();
		philo[i].time_to_die = ft_atoi(argv[2]);	
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].target_eats = -1;
		if (argc == 6)
			philo[i].target_eats = ft_atoi(argv[5]);
		philo[i].number_eats = 0;
		philo[i].last_eat = 0;
		philo->is_sleeping = 0;
		philo[i].total_philo = ft_atoi(argv[1]);
		philo[i].actions = ft_action_create();
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
	fork->mutex = malloc(sizeof(pthread_mutex_t) * f);
	if (fork->mutex == NULL)
		return (NULL);
	while (i < f)
	{
		fork->fork[i] = 0;
		pthread_mutex_init(&fork->mutex[i], NULL);
		i++;
	}
	return(fork);
}

t_action	*ft_action_create()
{
	t_action	*actions;
	int			i;

	actions = malloc(sizeof(t_action)* 5);
	if (!actions)
		return (NULL);
	i = 0;	
	while (i < 5)
	{
		actions[i].active = 0;
		actions[i].written = 0;
		i++;
	}
	actions[0].txt = "has taken a fork";
	actions[1].txt = "has taken a fork";
	actions[2].txt = "is eating";
	actions[3].txt = "is sleeping";
	actions[4].txt = "is thiking";
	return (actions);
}

int main( int argc, char **argv)
{
	t_philo *philo;
	t_fork	*fork;
	pthread_t *thread;
	t_philofork *philo_fork;
	int		a;
	long	time_death;
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
		philo_fork->philo = &philo[i];
		pthread_create(&thread[i], NULL, &routine, philo_fork);
		i++;
	}
	while(42)
	{
		i = 0;
		while(i < ft_atoi(argv[1]))
		{
			if(philo[i].is_sleeping == 1 && philo[i].is_sleeping_written == 0)
			{
				philo[i].is_sleeping_written = 1;
				print_stamp("is sleeping", philo[i]);
			}
			if(philo[i].is_thinking == 1 && philo[i].is_thinking_written == 0)
			{
				philo[i].is_thinking_written = 1;
				print_stamp("is thinking", philo[i]);
			}
			if(philo[i].right_fork == 1 && philo[i].right_fork_written == 0)
			{
				philo[i].right_fork_written = 1;
				print_stamp("has taken a fork", philo[i]);
			}
			if(philo[i].left_fork == 1 && philo[i].left_fork_written == 0)
			{
				philo[i].left_fork_written = 1;
				print_stamp("has taken a fork", philo[i]);
			}
			if(philo[i].left_fork == 1 && philo[i].right_fork == 1 && philo[i].is_eating_written == 0)
			{
				philo[i].is_eating_written = 1;
				print_stamp("is eating", philo[i]);
			}
			i++;
		}
		if(ft_getmineats(philo) == philo[0].target_eats)
		{
			i = 0;
			while(i < ft_atoi(argv[1]))
			{
				pthread_detach(thread[i]);
				i++;
			}
			printf("\nAll philosophers have eaten at least %d times\n", philo[0].target_eats);
			break;
		}
		i = 0;
		while( i < philo[0].total_philo)
		{
			if(my_gettime_ms() -  philo[i].last_eat - philo[i].birth > philo[i].time_to_die)
			{
				a = i;
				time_death = my_gettime_ms() - philo[i].birth;
				break;
			}
			i++;
		}
		if(i < philo[0].total_philo)
		{
			i = 0;
			while(i < ft_atoi(argv[1]))
			{
				pthread_detach(thread[i]);
				i++;
			}
			printf("\n");
			printf("%ld %d has died\n", time_death, a);
			break;
		}
	}

	return (0);
}