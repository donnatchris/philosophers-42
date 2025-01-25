/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:17:00 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 22:29:32 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	store_philosophers(t_dclst **agora, int nb_philo)
{
	int			i;
	t_timeval	time;

	*agora = NULL;
	gettimeofday(&time, NULL);
	i = 0;
	while (i < nb_philo)
	{
		dclst_add_back(agora, create_philosopher(agora, i + 1, time));
		i++;
	}
}

// Function to create a philosopher
t_philo	*create_philosopher(t_dclst **agora, int id, t_timeval time)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		error("Malloc failed", agora);
	philo->id = id;
	if (pthread_mutex_init(&philo->mutex, NULL))
		error("Mutex init failed", agora);
	philo->status = THINKING;
	philo->left_fork = id;
	philo->right_fork = (id + 1) % 5;
	philo->birth = time;
	philo->last_meal = time;
	return (philo);
}
