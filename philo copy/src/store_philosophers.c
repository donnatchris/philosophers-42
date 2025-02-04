/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:17:00 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 15:00:32 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	store_philosophers(t_dclst **agora, int nb_philo, t_rules *rules)
{
	int			i;
	long long	time;

	*agora = NULL;
	time = get_actual_time();
	i = 0;
	while (i < nb_philo)
	{
		dclst_add_back(agora, create_philosopher(agora, i + 1, time, rules));
		i++;
	}
}

// Function to create a philosopher
t_philo	*create_philosopher(t_dclst **agora, int id, long long time, t_rules *rules)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		error("Malloc failed", agora);
	philo->id = id;
	philo->last_meal = time;
	philo->n_meals = 0;
	philo->rules = rules;
	philo->last_meal_init = 0;
	philo->n_meal_init = 0;
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
		error("Mutex init failed", agora);
	philo->last_meal_init = 1;
	if (pthread_mutex_init(&philo->n_meals_mutex, NULL))
		error("Mutex init failed", agora);
	philo->n_meal_init = 1;

	if (pthread_mutex_init(&philo->fork, NULL))
		error("Mutex init failed", agora);
	
	return (philo);
}
