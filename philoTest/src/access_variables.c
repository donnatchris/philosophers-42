/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 06:04:41 by christophed       #+#    #+#             */
/*   Updated: 2025/01/30 06:47:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to read or change a philosopher status
int	access_status(t_philo *philo, int mode, int new_status)
{
	int	status;

	pthread_mutex_lock(&philo->m_status);
	if (mode == WRITE)
		philo->status = new_status;
	status = philo->status;
	pthread_mutex_unlock(&philo->m_status);
	return (status);
}

// Function to read or change the run_threads variable
int	access_run_thread(t_rules *rules, int mode, int new_value)
{
	int	run_threads;

	pthread_mutex_lock(&rules->m_run_threads);
	if (mode == WRITE)
		rules->run_threads = new_value;
	run_threads = rules->run_threads;
	pthread_mutex_unlock(&rules->m_run_threads);
	return (run_threads);
}
