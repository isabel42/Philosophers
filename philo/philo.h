/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:09:05 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/07 22:23:16 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

enum e_act {righ_fork, left_fork, eating, sleeping, thinking};

typedef struct s_philo {
	int			id;
	long		birth;
	long		death;
	long		last_eat;
	int			number_eats;
}				t_philo;

typedef struct s_mulmutex {
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_total_eats;
}				t_mulmutex;

typedef struct s_info {
	long		time_to_die;	
	long		time_to_eat;
	long		time_to_sleep;
	int			target_eats;
	int			total_philo;
	char		**actions;
	int			stop;
	t_mulmutex	*mul_mutex;
}				t_info;

typedef struct s_philoinfo {
	t_philo			*philo;
	t_info			*info;
}				t_philoinfo;

// philo_utils.c
int					ft_atoi(const char *str);
int					ft_strlen(char *s);
void				print_stamp(char *mess, t_philo philo);
long				my_gettime_ms(void);
int					ft_getmineats(t_philo *philo, t_info *info);

// routine.c
void				ft_write(int i, t_philo *philo, t_info *info);
void				ft_eat(t_philo *philo, t_info *info);
void				ft_lock_mutex(t_info *info, t_philo *philo);
void				ft_unlock_mutex(t_info *info, t_philo *philo);
void				*routine(void *philo_fork);

// philo_fork_creation.c 
t_info				*ft_info(int argc, char **argv);
t_philo				*ft_philocreate(char **argv);
t_mulmutex			*ft_mutex(int f);
char				**ft_action_create(void);
int					ft_thread(t_philo *philo, t_info *info,
						pthread_t *thread, t_philoinfo **philo_info);

// free.c
void				ft_free_all(t_philo *philo, t_info *info,
						t_philoinfo **philo_info, pthread_t *thread);

// arg_check.c
int					ft_check_digit(int argc, char **argv);
int					ft_check_int(int argc, char **argv);
int					ft_check_arg(int argc, char **argv);

//end_check.c
int					ft_eat_total(int i, t_philo *philo, t_info *info);
int					ft_death_time(int i, t_philo *philo, t_info *info);

#endif