/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:25:10 by christophed       #+#    #+#             */
/*   Updated: 2025/01/29 11:47:19 by chdonnat         ###   ########.fr       */
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
	philo_think(node);
	if (philo->id % 2 == 0)
		usleep(900);
	while (philo->status != DEAD && philo->rules->run_threads)
	{
		if (philo->status != DEAD && philo->rules->run_threads)
			philo_eat(node);
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
	philo->status = THINKING;
	if (philo->status != DEAD && philo->rules->run_threads)
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
	philo->status = FORK;
	write_log(philo);
	pthread_mutex_lock(&next_philo->fork);
	write_log(philo);
	philo->status = EATING;
	write_log(philo);
	usleep(philo->rules->time_to_eat * 1000);
	gettimeofday(&philo->last_meal, NULL);
	philo->n_meals++;
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

// // Function to take forks
// void	take_forks(t_philo *philo, pthread_mutex_t *g_fork, pthread_mutex_t	*r_fork)
// {
// 	pthread_mutex_lock(g_fork);
// 	philo->status = FORK;
// 	write_log(philo);
// 	pthread_mutex_lock(r_fork);
// 	write_log(philo);
// }

// Function to handle sleeping
void	philo_sleep(t_dclst *node)
{
	t_philo	*philo;

	philo = (t_philo *)node->data;
	philo->status = SLEEPING;
	philo->status = FORK;
	if (philo->status != DEAD && philo->rules->run_threads)
		write_log(philo);
	usleep(philo->rules->time_to_sleep * 1000);
}
