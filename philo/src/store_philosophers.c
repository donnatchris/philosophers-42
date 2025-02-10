/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:17:00 by christophed       #+#    #+#             */
/*   Updated: 2025/02/10 12:16:21 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	store_philosophers(t_dclst **agora, int nb_philo, t_rules *rules)
{
	int				i;
	long long		time;
	pthread_mutex_t	*forks;

	*agora = NULL;
	time = get_actual_time();
	i = 0;
	while (i < nb_philo)
	{
		dclst_add_back(agora, create_philosopher(agora, i + 1, time, rules));
		i++;
	}
	forks = create_forks(nb_philo);
	if (!forks)
		error("Malloc failed", rules, agora);
	give_forks(*agora, forks, nb_philo);
}

// Function to create a philosopher
t_philo	*create_philosopher(t_dclst **agora, int id, long long time, \
		t_rules *rules)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		error("Malloc failed", rules, agora);
	philo->id = id;
	philo->last_meal = time;
	philo->n_meals = 0;
	philo->rules = rules;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	philo->last_meal_init = 0;
	philo->n_meal_init = 0;
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
		error("Mutex init failed", rules, agora);
	philo->last_meal_init = 1;
	if (pthread_mutex_init(&philo->n_meals_mutex, NULL))
		error("Mutex init failed", rules, agora);
	philo->n_meal_init = 1;
	return (philo);
}

// Function to create an array of forks
pthread_mutex_t	*create_forks(int nb_philo)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			destroy_forks(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

// Function to give forks to the philosophers
void	give_forks(t_dclst *agora, pthread_mutex_t *forks, int nb_philo)
{
	t_dclst	*current;
	t_philo	*philo;

	current = agora;
	while (current != NULL)
	{
		philo = (t_philo *)current->data;
		philo->left_fork = &forks[philo->id - 1];
		if (philo->id == nb_philo)
			philo->right_fork = &forks[0];
		else
			philo->right_fork = &forks[philo->id];
		current = current->next;
		if (current == agora)
			break ;
	}
}
