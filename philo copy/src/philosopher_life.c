/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 14:43:12 by christophed      ###   ########.fr       */
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
	philo_think(philo);
	if (philo->id % 2 == 0)
		usleep(900);
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

void	philo_think(t_philo *philo)
{
	write_log(philo, THINK);
}

// Function to handle eating
void	philo_eat(t_dclst *node)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = (t_philo *)node->data;
	next_philo = (t_philo *)node->next->data;
	pthread_mutex_lock(&philo->fork);
	write_log(philo, FORK);
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(&next_philo->fork);
	write_log(philo, FORK);
	write_log(philo, EAT);
	usleep(philo->rules->time_to_eat * 1000);
	philo->last_meal = get_actual_time();
	philo->n_meals++;
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	philo_sleep(t_philo *philo)
{
	write_log(philo, SLEEP);
	usleep(philo->rules->time_to_sleep * 1000);
}