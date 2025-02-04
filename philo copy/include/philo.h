/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:27:01 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 16:30:50 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Libraries
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include "dclst.h"

// Constants
# define THINK 0
# define FORK 1
# define EAT 2
# define SLEEP 3
# define DEAD 4
# define WON 5
# define READ 0
# define STOP 1
# define WRITE 2

// Structures and typedefs
typedef struct timeval	t_timeval;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				run_threads;
	pthread_mutex_t	run_mutex;
	pthread_mutex_t	log_mutex;
}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				n_meals;
	pthread_mutex_t	n_meals_mutex;
	int				n_meal_init;
	long long		last_meal;
	pthread_mutex_t last_meal_mutex;
	int				last_meal_init;
	t_rules			*rules;
}					t_philo;

/*********************************************************/
/*                  Functions in utils/                  */
/*********************************************************/
/******************* utils_function.c ********************/
long		ft_atoi_long(const char *nptr);
long long	timeval_to_ms(t_timeval time);
long long	get_actual_time(void);
long long	get_elapsed_time(long long event);
/*********************************************************/
/*                   Functions in src/                   */
/*********************************************************/
/********************* store_rules.c *********************/
void			store_rules(t_rules *rules, int ac, char **av);
void			control_and_store(long n, int *rule);
void			control_rules(long n);
int				is_positive_int(long n);
void			print_rules(t_rules rules);
/***************** store_philosophers.c ******************/
void			store_philosophers(t_dclst **agora, int nb_philo, t_rules *rules);
t_philo			*create_philosopher(t_dclst **agora, \
	int id, long long time, t_rules *rules);
pthread_mutex_t	*create_forks(int nb_philo);
void			give_forks(t_dclst *agora, pthread_mutex_t *forks, int nb_philo);
/****************** launch_simulation.c ******************/
void			launch_simu(t_dclst **agora, t_rules rules, int n_threads);
void			create_threads(t_dclst **agora, \
	t_rules rules, pthread_t *threads, int n_threads);
void			join_threads(pthread_t *threads, int n_threads);
/************************ survey.c ***********************/
void			*survey_dead(void *arg);
void			*survey_win(void *arg);
int				have_won(t_dclst *current, t_rules *rules);
/******************* philosopher_life.c ******************/
void			*philosopher_life(void *arg);
void			philo_think(t_philo *philo);
void			philo_eat(t_dclst *node);
void			philo_sleep(t_philo *philo);
/******************** mutex_functions.c ******************/
int				check_run(t_rules *rules, int mode);
long long		check_last_meal(t_philo *philo, int mode);
int				check_n_meals(t_philo *philo, int mode);
void			write_log(t_philo *philo, int status);
/********************* close_prgram.c ********************/
void			error(char *message, t_dclst **agora);
void			free_and_exit(t_dclst **agora, int status);
void			destroy_philo_mutexes(t_dclst **agora);
void			destroy_forks(pthread_mutex_t *forks, int nb_forks);

#endif
