/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/01/28 00:47:40 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to simulate the life of a philosopher
void	*philosopher_life(void *arg)
{
	t_dclst *node;
	t_philo	*philo;

	node = (t_dclst *)arg;
	philo = (t_philo *)node->data;
	while (philo->status != DEAD && philo->rules->run_threads)
	{
		philo_think(node);
		if (philo->id % 2 == 0)
		{
			philo_eat(node);
			philo_sleep(node);
		}
		else
		{
			philo_sleep(node);
			philo_eat(node);
		}
	}
	return (NULL);
}

// Function to handle thinking
void	philo_think(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	philo->status = THINKING;
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
	pthread_mutex_lock(&next_philo->fork);
	philo->status = FORK;
	write_log(philo);
	philo->status = EATING;
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
	philo->status = SLEEPING;
	write_log(philo);
	usleep(philo->rules->time_to_sleep * 1000);
}
