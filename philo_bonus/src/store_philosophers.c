/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:17:00 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 14:30:50 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	store_philosophers(t_dclst **agora, int nb_philo, t_rules *rules)
{
	int				i;
	long long		time;
	sem_t			*forks;

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
t_philo	*create_philosopher(t_dclst **agora, int id, long long time, \
		t_rules *rules)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		error("Malloc failed", rules, agora);
	philo->last_meal_init = 0;
	philo->n_meals_init = 0;
	philo->id = id;
	philo->last_meal = time;
	philo->n_meals = 0;
	philo->rules = rules;
	philo->last_meal_sem = sem_open("/last_meal_lock", O_CREAT, 0644, 1);
	if (philo->last_meal_sem == SEM_FAILED)
		error("sem_open failed", rules, agora);
	philo->last_meal_init = 1;
	philo->n_meals_sem = sem_open("/n_meals_lock", O_CREAT, 0644, 1);
	if (philo->n_meals_sem == SEM_FAILED)
		error("sem_open failed", rules, agora);
	philo->n_meals_init = 1;
	return (philo);
}
