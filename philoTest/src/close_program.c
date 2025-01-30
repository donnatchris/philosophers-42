/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/01/30 06:55:38 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to exit the program and free memory
void	free_and_exit(t_dclst **agora, int status)
{
	t_rules	*rules;

	if (agora)
	{
		rules = ((t_philo *)(*agora)->data)->rules;
		pthread_mutex_destroy(&rules->m_log);
		pthread_mutex_destroy(&rules->m_run_threads);
		destroy_mutex(agora);
		dclst_clear(agora);
		printf("End of simulation\n");
	}
	exit(status);
}

// Function to destroy the mutexes of the philosophers
void	destroy_mutex(t_dclst **agora)
{
	t_dclst	*current;
	t_philo	*philo;

	if (agora == NULL || *agora == NULL)
		return ;
	current = *agora;
	while (current != NULL)
	{
		philo = (t_philo *)current->data;
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->m_status);
		current = current->next;
		if (current == *agora)
			break ;
	}
}

// Function to print an error message and free the agora list
void	error(char *message, t_dclst **agora)
{
	printf("Error: %s\n", message);
	free_and_exit(agora, 1);
}

// Function to print the death of a philosopher
void	bad_end(t_philo *philo)
{
	access_status(philo, WRITE, DEAD);
	write_log(philo, access_status(philo, READ, 0));
	// philo->rules->nb_must_eat = 0;
	// philo->rules->time_to_die = 0;
}

// Function to stop the simulation after all philosophers have eaten enough
void	happy_end(t_philo *philo)
{
	access_status(philo, WRITE, WON);
	write_log(philo, access_status(philo, READ, 0));
	// philo->rules->nb_must_eat = 0;
	// philo->rules->time_to_die = 0;
}
