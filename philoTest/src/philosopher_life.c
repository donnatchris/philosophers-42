/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/01/30 06:57:04 by christophed      ###   ########.fr       */
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
	while (access_run_thread(philo->rules, READ, 0))
	{
		if (access_run_thread(philo->rules, READ, 0))
			philo_eat(node);
		if (philo->rules->nb_philo == 1)
			break ;
		if (access_run_thread(philo->rules, READ, 0))
			philo_sleep(node);
		if (access_run_thread(philo->rules, READ, 0))
			philo_think(node);
	}
	return (NULL);
}

// Function to handle thinking
void	philo_think(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	access_status(philo, WRITE, THINKING);
	write_log(philo, access_status(philo, READ, 0));
}

// Function to handle eating
void	philo_eat(t_dclst *node)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = (t_philo *)node->data;
	next_philo = (t_philo *)node->next->data;
	pthread_mutex_lock(&philo->fork);
	access_status(philo, WRITE, FORK);
	write_log(philo, access_status(philo, READ, 0));
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(&next_philo->fork);
	write_log(philo, access_status(philo, READ, 0));
	access_status(philo, WRITE, EATING);
	write_log(philo, access_status(philo, READ, 0));
	usleep(philo->rules->time_to_eat * 1000);
	gettimeofday(&philo->last_meal, NULL);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&next_philo->fork);
}

// Function to handle sleeping
void	philo_sleep(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	access_status(philo, WRITE, SLEEPING);
	write_log(philo, access_status(philo, READ, 0));
	usleep(philo->rules->time_to_sleep * 1000);
}
