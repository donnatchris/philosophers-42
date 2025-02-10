/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/02/10 12:41:05 by christophed      ###   ########.fr       */
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
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		usleep(500);
	}
	while (check_run(philo->rules, READ))
	{
		philo_eat(node);
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
	write_log(philo, THINK);
}

// Function to handle eating
void	philo_eat(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	pthread_mutex_lock(philo->left_fork);
	write_log(philo, FORK);
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	write_log(philo, FORK);
	write_log(philo, EAT);
	check_last_meal(philo, WRITE);
	usleep(philo->rules->time_to_eat * 1000);
	check_n_meals(philo, WRITE);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// Function to handle sleeping
void	philo_sleep(t_philo *philo)
{
	write_log(philo, SLEEP);
	usleep(philo->rules->time_to_sleep * 1000);
}
