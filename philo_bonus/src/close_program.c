/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 14:58:50 by chdonnat         ###   ########.fr       */
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
	t_philo	*first_philo;
	
	if (rules)
		destroy_rules_sem(rules);
	if (agora)
	{
		first_philo = (t_philo *)(*agora)->data;
		destroy_philo_sem(agora);
		dclst_clear(agora);
	}
	exit(status);
}

// Function to destroy the forks
void	destroy_rules_sem(t_rules *rules)
{
	if (!rules)
		return ;
	if (rules->forks_sem_init)
	{
		sem_close(rules->forks_sem);
		sem_unlink("/forks_lock");
	}
	if (rules->log_sem_init)
	{
		sem_close(rules->log_sem);
		sem_unlink("/log_lock");
	}
	if (rules->run_sem_init)
	{
		sem_close(rules->run_sem);
		sem_unlink("/run_lock");
	}
	
}

// Function to destroy the mutexes of the philosophers
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
			sem_unlink("/last_meal_lock");
		}
		if (philo->n_meals_init)
		{
			sem_close(philo->n_meals_sem);
			sem_unlink("/n_meals_lock");
		}
		current = current->next;
		if (current == *agora)
			break ;
	}
}
