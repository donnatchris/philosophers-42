/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/02/10 13:20:16 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

// Function to destroy all semaphores in the rules structure
void	destroy_rules_sem(t_rules *rules)
{
	if (!rules)
		return ;
	if (rules->forks_sem_init)
		destroy_sem(rules->forks_sem, "/forks_sem");
	if (rules->log_sem_init)
		destroy_sem(rules->log_sem, "/log_sem");
	if (rules->win_sem_init)
		destroy_sem(rules->win_sem, "/win_sem");
	if (rules->end_sem_init)
		destroy_sem(rules->end_sem, "/end_sem");
}

// Function to destroy the semaphores of all the philosophers
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
			destroy_sem(philo->last_meal_sem, "/last_meal_sem");
		current = current->next;
		if (current == *agora)
			break ;
	}
}

// Function to destroy a semaphore
void	destroy_sem(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}
