/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:45:41 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 14:28:52 by chdonnat         ###   ########.fr       */
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
	rules->run_sem_init = 0;
	rules->forks_sem_init = 0;
	rules->log_sem_init = 0;
	control_and_store(nb_philo, &rules->nb_philo, rules);
	control_and_store(time_to_die, &rules->time_to_die, rules);
	control_and_store(time_to_eat, &rules->time_to_eat, rules);
	control_and_store(time_to_sleep, &rules->time_to_sleep, rules);
	rules->run_threads = 1;
	if (ac == 6)
		control_and_store(nb_must_eat, &rules->nb_must_eat, rules);
	else
		rules->nb_must_eat = -1;
	create_rules_sem(rules);
}

// Function to control then store a rule
void	control_and_store(long n, int *rule, t_rules *rules)
{
	if (!(n <= 2147483647 && n > 0))
		error("Invalid input", rules, NULL);
	*rule = (int) n;
}

// Function to create all the semaphores in the rules structure
void	create_rules_sem(t_rules *rules)
{
	rules->forks_sem = sem_open("/forks_lock", O_CREAT, 0644, (unsigned int) rules->nb_philo);
	if (rules->forks_sem == SEM_FAILED)
		error("sem_open failure", rules, NULL);
	rules->forks_sem = 1;
	rules->run_sem = sem_open("/run_lock", O_CREAT, 0644, 1);
	if (rules->run_sem == SEM_FAILED)
		error("sem_open failure", rules, NULL);
	rules->run_sem = 1;
	rules->log_sem = sem_open("/log_lock", O_CREAT, 0644, 1);
	if (rules->log_sem == SEM_FAILED)
		error("sem_open failure", rules, NULL);
	rules->log_sem = 1;
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
