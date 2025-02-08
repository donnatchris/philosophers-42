/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:37:31 by christophed       #+#    #+#             */
/*   Updated: 2025/02/08 12:51:30 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// Libraries
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
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

# define RESET "\033[0m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define GRAY "\033[1;37m"
# define BROWN "\033[0;33m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"

// Structures and typedefs
typedef struct timeval	t_timeval;

typedef struct s_rules
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_must_eat;
	sem_t		*forks_sem;
	int			forks_sem_init;
	sem_t		*log_sem;
	int			log_sem_init;
	sem_t		*win_sem;
	int			win_sem_init;
	sem_t		*end_sem;
	int			end_sem_init;
}				t_rules;

typedef struct s_philo
{
	int			id;
	int			n_meals;
	long long	last_meal;
	sem_t		*last_meal_sem;
	int			last_meal_init;
	t_rules		*rules;
}				t_philo;

/* ************************************************************************** */
/*									utils_function.c 						  */
/* ************************************************************************** */
long		ft_atoi_long(const char *nptr);
long long	timeval_to_ms(t_timeval time);
long long	get_actual_time(void);
long long	get_elapsed_time(long long event);
/* ************************************************************************** */
/*									store_rules.c 						 	  */
/* ************************************************************************** */
void		store_rules(t_rules *rules, int ac, char **av);
void		control_and_store(long n, int *rule, t_rules *rules);
void		create_rules_sem(t_rules *rules);
void		print_rules(t_rules rules);
/* ************************************************************************** */
/*								store_philosophers.c 						  */
/* ************************************************************************** */
void		store_philosophers(t_dclst **agora, int nb_philo, t_rules *rules);
t_philo		*create_philosopher(t_dclst **agora, int id, long long time, \
			t_rules *rules);
/* ************************************************************************** */
/*								launch_simulation.c 						  */
/* ************************************************************************** */
void		launch_simu(t_dclst **agora, t_rules *rules);
void		create_survey_process(pid_t *pid, t_dclst **agora, t_rules *rules);
void		create_philo_processes(pid_t *pid, t_dclst **agora, t_rules *rules, pid_t survey_pid);
void		kill_processes(pid_t *pid, int nb);
void		write_log(t_philo *philo, int status);
/* ************************************************************************** */
/*									philosopher_life.c 						  */
/* ************************************************************************** */
void		*philosopher_life(void *arg);
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
/* ************************************************************************** */
/*										survey.c 							  */
/* ************************************************************************** */
void		*survey_win(t_rules *rules);
void		*survey_dead(void *arg);
long long	check_last_meal(t_philo *philo, int mode);
/* ************************************************************************** */
/*									close_program.c 						  */
/* ************************************************************************** */
void		error(char *message, t_rules *rules, t_dclst **agora);
void		free_and_exit(t_rules *rules, t_dclst **agora, int status);
void		destroy_rules_sem(t_rules *rules);
void		destroy_philo_sem(t_dclst **agora);
void		destroy_sem(sem_t *sem, char *name);

#endif
