/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/01/29 20:47:07 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to simulate the life of a philosopher
void	*philosopher_life(void *arg)
{
	t_dclst	*node;
	t_philo	*philo;

	node = (t_dclst *)arg;
	philo = (t_philo *)node->data;
	philo_think(node);
	if (philo->id % 2 == 0)
		usleep(900);
	while (philo->status != DEAD && philo->rules->run_threads)
	{
		if (philo->status != DEAD && philo->rules->run_threads)
			philo_eat(node);
		if (philo->rules->nb_philo == 1)
			break ;
		if (philo->status != DEAD && philo->rules->run_threads)
			philo_sleep(node);
		if (philo->status != DEAD && philo->rules->run_threads)
			philo_think(node);
	}
	return (NULL);
}

// Function to handle thinking
void	philo_think(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	change_status(philo, THINKING);
	write_log(philo);
}

// Function to handle eating
void	philo_eat(t_dclst *node)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = (t_philo *)node->data;
	next_philo = (t_philo *)node->next->data;
	pthread_mutex_lock(&philo->fork);
	change_status(philo, FORK);
	write_log(philo);
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(&next_philo->fork);
	write_log(philo);
	change_status(philo, EATING);
	write_log(philo);
	usleep(philo->rules->time_to_eat * 1000);
	gettimeofday(&philo->last_meal, NULL);
	philo->n_meals++;
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

// Function to handle sleeping
void	philo_sleep(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	change_status(philo, SLEEPING);
	write_log(philo);
	usleep(philo->rules->time_to_sleep * 1000);
}

// Function to change a philosopher status
void	change_status(t_philo *philo, int new_status)
{
	pthread_mutex_lock(&philo->m_status);
	philo->status = new_status;
	pthread_mutex_unlock(&philo->m_status);
}
