/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:45:41 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 18:50:37 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to store the rules
void	store_input(t_rules *rules, int ac, char **av)
{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_must_eat;

	if (ac != 5 && ac != 6)
		error("Invalid number of arguments", NULL);
	nb_philo = ft_atoi_long(av[1]);
	time_to_die = ft_atoi_long(av[2]);
	time_to_eat = ft_atoi_long(av[3]);
	time_to_sleep = ft_atoi_long(av[4]);
	if (ac == 6)
		nb_must_eat = ft_atoi_long(av[5]);
	control_and_store(nb_philo, &rules->nb_philo);
	control_and_store(time_to_die, &rules->time_to_die);
	control_and_store(time_to_eat, &rules->time_to_eat);
	control_and_store(time_to_sleep, &rules->time_to_sleep);
	if (ac == 6)
		control_and_store(nb_must_eat, &rules->nb_must_eat);
	else
		rules->nb_must_eat = -1;
}

// Function to control then store a rule
void	control_and_store(long n, int *rule)
{
	if (!is_positive_int(n))
		error("Invalid input", NULL);
	*rule = (int) n;
}

// Function to control if the input rules are valid
void	control_rules(long n)
{
	if (!is_positive_int(n))
		error("Invalid input", NULL);
}

// Function to see if the number is a positive integer
int	is_positive_int(long n)
{
	if (n <= 2147483647 && n > 0)
		return (1);
	return (0);
}
