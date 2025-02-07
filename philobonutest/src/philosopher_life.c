/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/02/07 22:43:45 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to simulate the life of a philosopher
void	*philosopher_life(void *arg)
{
	t_dclst		*node;
	t_philo		*philo;
	pthread_t	thread;

	node = (t_dclst *)arg;
	philo = (t_philo *)node->data;
	if (pthread_create(&thread, NULL, survey_dead, philo) != 0)
		return (NULL);
	if (pthread_detach(thread) != 0)
		return (NULL);
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		usleep(1000);
	}
	while (1)
	{
		philo_eat(philo);
		if (philo->rules->nb_philo == 1)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

// Function to handle thinking
void	philo_think(t_philo *philo)
{
	sem_wait(philo->rules->log_sem);
	write_log(philo, THINK);
	sem_post(philo->rules->log_sem);
}

// Function to handle eating
void	philo_eat(t_philo *philo)
{
	sem_wait(philo->rules->forks_sem);
	sem_wait(philo->rules->log_sem);
	write_log(philo, FORK);
	sem_post(philo->rules->log_sem);
	if (philo->rules->nb_philo == 1)
	{
		sem_post(philo->rules->forks_sem);
		return ;
	}
	sem_wait(philo->rules->forks_sem);
	sem_wait(philo->rules->log_sem);
	write_log(philo, FORK);
	write_log(philo, EAT);
	sem_post(philo->rules->log_sem);
	check_last_meal(philo, WRITE);
	usleep(philo->rules->time_to_eat * 1000);
	philo->n_meals++;
	if (philo->rules->nb_must_eat != -1)
		if (philo->n_meals == philo->rules->nb_must_eat)
			sem_post(philo->rules->win_sem);
	sem_post(philo->rules->forks_sem);
	sem_post(philo->rules->forks_sem);
}

// Function to handle sleeping
void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->rules->log_sem);
	write_log(philo, SLEEP);
	sem_post(philo->rules->log_sem);
	usleep(philo->rules->time_to_sleep * 1000);
}
