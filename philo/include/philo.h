/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:27:01 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 20:49:16 by christophed      ###   ########.fr       */
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
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

// Structures
typedef struct timeval	t_timeval;

typedef struct s_rules
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;
}		t_rules;

typedef struct s_philo
{
	int				id;
	t_timeval		birth;
	int				status;
	t_timeval		last_meal;
	int				left_fork;
	int				right_fork;
}					t_philo;

// Functions
void	error(char *message, t_dclst **philo);
void	store_input(t_rules *rules, int ac, char **av);
void	control_and_store(long n, int *rule);
void	control_rules(long n);
int		is_positive_int(long n);
long	ft_atoi_long(const char *nptr);
void	print_rules(t_rules rules);
void	print_dead(int	id);
void	store_philosophers(t_dclst **agora, int nb_philo);
t_philo	*create_philosopher(t_dclst **agora, int id);

#endif