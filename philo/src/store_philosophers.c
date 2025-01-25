/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:17:00 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 20:45:31 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	store_philosophers(t_dclst **agora, int nb_philo)
{
	int	i;

	*agora = NULL;
	i = 0;
	while (i < nb_philo)
	{
		dclst_add_back(agora, create_philosopher(agora, i + 1));
		i++;
	}
}

t_philo	*create_philosopher(t_dclst **agora, int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		error("Malloc failed", agora);
	philo->id = id;
	philo->status = THINKING;
	philo->left_fork = id;
	philo->right_fork = (id + 1) % 5;
	gettimeofday(&philo->birth, NULL);
	gettimeofday(&philo->last_meal, NULL);
	return (philo);
}
