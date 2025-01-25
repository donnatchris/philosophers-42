/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:27:01 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 12:06:51 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Libraries
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

// Structures
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
	int				left_fork;
	int				right_fork;
	int				meals;
	struct s_philo	*next;
}	t_philo;

// Functions
void	error(char *message);
void	store_input(t_rules *rules, int ac, char **av);
void	control_and_store(long n, int *rule);
void	control_rules(long n);
int		is_positive_int(long n);
long	ft_atoi_long(const char *nptr);


#endif
