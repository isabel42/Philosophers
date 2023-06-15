/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:09:05 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/15 14:42:04 by itovar-n         ###   ########.fr       */
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
	int				id;
	int				birth;
	int				death;
	int				last_eat;
	int				number_eats;
	int				time_to_die;	
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				total_philo;
	pthread_mutex_t	*mutex_local;
}				t_philo;

typedef struct s_mulmutex {
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	*mutex_local;
	pthread_mutex_t	mutex_stop;
}				t_mulmutex;

typedef struct s_info {
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
void				print_stamp(char *mess, t_philo philo);
int					my_gettime_ms(void);
void				ft_write(int i, t_philo *philo, t_info *info);
void				my_usleep(int waiting_time, t_info *info);

// routine.c
int					ft_stop_check(int *stop, pthread_mutex_t *mutex_stop);
int					ft_update(int *numb_eats,
						int new_numb_eats, pthread_mutex_t *mutex_local);
int					ft_get_tot_philo(t_philo *philo);
int					ft_eat(t_philo *philo, t_info *info);
void				*routine(void *philo_fork);

// philo_fork_creation.c 
t_info				*ft_info(int argc, char **argv);
t_philo				*ft_philocreate(char **argv, t_mulmutex *mul_mutex);
t_mulmutex			*ft_mutex(int f);
char				**ft_action_create(void);
int					ft_thread(t_philo *philo, t_info *info,
						pthread_t *thread, t_philoinfo **philo_info);

// free.c
void				ft_free_all(t_philo *philo, t_info *info,
						t_philoinfo **philo_info, pthread_t *thread);

// arg_check.c
int					ft_strlen(char *s);
int					ft_check_digit(int argc, char **argv);
int					ft_check_int(int argc, char **argv);
int					ft_check_arg(int argc, char **argv);

//ft_check_exit.c
void				ft_cp_die_eat_birth(t_philo *philo,
						int *cp_time_to_die, int *cp_last_eat, int *cp_birth);
void				philo_die(t_philo *philo, t_info *info);
void				ft_get_min_eat(t_philo *philo, int *min_eat);
void				ft_join(t_info *info, pthread_t *thre);
void				ft_check_exit(t_philo *philo,
						pthread_t *thread, t_info *info);
#endif