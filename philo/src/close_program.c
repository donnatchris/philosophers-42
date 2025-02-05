/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/02/05 14:00:40 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to print an error message and free the agora list
void	error(char *message, t_dclst **agora)
{
	printf("Error: %s\n", message);
	free_and_exit(agora, 1);
}

// Function to exit the program and free memory
void	free_and_exit(t_dclst **agora, int status)
{
	t_rules	*rules;
	t_philo	*first_philo;

	if (agora)
	{
		first_philo = (t_philo *)(*agora)->data;
		rules = ((t_philo *)(*agora)->data)->rules;
		pthread_mutex_destroy(&rules->log_mutex);
		pthread_mutex_destroy(&rules->run_mutex);
		destroy_forks(first_philo->left_fork, rules->nb_philo);
		destroy_philo_mutexes(agora);
		dclst_clear(agora);
	}
	exit(status);
}

// Function to destroy the mutexes of the philosophers
void	destroy_philo_mutexes(t_dclst **agora)
{
	t_dclst	*current;
	t_philo	*philo;

	if (agora == NULL || *agora == NULL)
		return ;
	current = *agora;
	while (current != NULL)
	{
		philo = (t_philo *)current->data;
		if (philo->last_meal_init)
			pthread_mutex_destroy(&philo->last_meal_mutex);
		if (philo->n_meal_init)
			pthread_mutex_destroy(&philo->n_meals_mutex);
		current = current->next;
		if (current == *agora)
			break ;
	}
}

// Function to destroy the forks
void	destroy_forks(pthread_mutex_t *forks, int nb_forks)
{
	int	i;

	i = 0;
	while (i < nb_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
