/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:45:41 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 19:26:45 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to store the rules
void	store_rules(t_rules *rules, int ac, char **av)
{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_must_eat;

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
	rules->run_threads = 1;
	if (ac == 6)
		control_and_store(nb_must_eat, &rules->nb_must_eat);
	else
		rules->nb_must_eat = -1;
	if (pthread_mutex_init(&rules->log_mutex, NULL) != 0)
		error("mutex init failed", NULL);
	if (pthread_mutex_init(&rules->run_mutex, NULL) != 0)
		error("mutex init failed", NULL);
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

// Function to print the rules
void	print_rules(t_rules rules)
{
	printf("\n*************************  Rules  *************************\n");
	printf("Number of philosophers:\t\t\t\t%d\n", rules.nb_philo);
	printf("Time to die:\t\t\t\t\t%d\n", rules.time_to_die);
	printf("Time to eat:\t\t\t\t\t%d\n", rules.time_to_eat);
	printf("Time to sleep:\t\t\t\t\t%d\n", rules.time_to_sleep);
	if (rules.nb_must_eat == -1)
		printf("Number of times each philosopher must eat:\tuntil death\n");
	else
		printf("Number of times each philosopher must eat:\t%d\n", \
		rules.nb_must_eat);
	printf("***********************************************************\n\n");
}
