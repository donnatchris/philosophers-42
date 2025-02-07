/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:17:00 by christophed       #+#    #+#             */
/*   Updated: 2025/02/07 21:07:28 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to store all the philosophers
void	store_philosophers(t_dclst **agora, int nb_philo, t_rules *rules)
{
	int				i;
	long long		time;

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
	memset(philo, 0, sizeof(t_philo));
	philo->id = id;
	philo->last_meal = time;
	philo->rules = rules;
	sem_unlink("/last_meal_sem");
	philo->last_meal_sem = sem_open("/last_meal_sem", O_CREAT, 0644, 1);
	if (philo->last_meal_sem == SEM_FAILED)
		error("sem_open failed", rules, agora);
	philo->last_meal_init = 1;
	return (philo);
}
