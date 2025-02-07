/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 20:46:41 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to print an error message and free the agora list
void	error(char *message, t_rules *rules, t_dclst **agora)
{
	printf("Error\n%s\n", message);
	free_and_exit(rules, agora, 1);
}

// Function to exit the program and free memory
void	free_and_exit(t_rules *rules, t_dclst **agora, int status)
{	
	if (rules)
		destroy_rules_sem(rules);
	if (agora)
	{
		destroy_philo_sem(agora);
		dclst_clear(agora);
	}
	exit(status);
}

// Function to destroy the semaphores in the rules structure
void	destroy_rules_sem(t_rules *rules)
{
	if (!rules)
		return ;
	if (rules->forks_sem_init)
	{
		sem_close(rules->forks_sem);
		sem_unlink("/forks_sem");
	}
	if (rules->log_sem_init)
	{
		sem_close(rules->log_sem);
		sem_unlink("/log_sem");
	}
	if (rules->run_sem_init)
	{
		sem_close(rules->run_sem);
		sem_unlink("/run_sem");
	}
	
}

// Function to destroy the semaphores in the philosophers structure
void	destroy_philo_sem(t_dclst **agora)
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
		{
			sem_close(philo->last_meal_sem);
			sem_unlink("/last_meal_sem");
		}
		if (philo->n_meals_init)
		{
			sem_close(philo->n_meals_sem);
			sem_unlink("/n_meals_sem");
		}
		current = current->next;
		if (current == *agora)
			break ;
	}
}
