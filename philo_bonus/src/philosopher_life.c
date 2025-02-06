/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 11:32:40 by chdonnat         ###   ########.fr       */
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

void	philo_think(t_philo *philo)
{
	write_log(philo, THINK);
}

// Function to handle eating
void	philo_eat(t_dclst *node)
{
	t_philo	*philo;
	int		meals;

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
	meals = check_n_meals(philo, WRITE);
	if (philo->rules->nb_must_eat != -1)
		if (meals >= philo->rules->nb_must_eat)
			if (check_victory(node, philo->rules))
				write_log(philo, WON);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	write_log(philo, SLEEP);
	usleep(philo->rules->time_to_sleep * 1000);
}
