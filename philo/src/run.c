/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 23:35:46 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to run the simulation
void	run_simulation(t_dclst **agora, t_rules rules)
{
	(void)agora;
	(void)rules;
}

// Function to survey the philosophers
void	survey(t_dclst **agora, t_rules rules)
{
	t_dclst	*current;
	t_philo	*philo;
	int		i;

	current = *agora;
	i = 0;
	while (i < rules.nb_philo)
	{
		philo = current->data;
		if (philo->status == DEAD)
			write_log(agora, philo, DEAD);
		if (get_elapsed_time(philo->last_meal) > rules.time_to_die)
			write_log(agora, philo, DEAD);
		current = current->next;
		i++;
		// need to add a rule to see if all philosophers have eaten enough
	}
}

// Function to write logs
void	write_log(t_dclst **agora, t_philo *philo, int status)
{
	// manque "has tah$ken a fork"
	pthread_mutex_lock(&philo->mutex);
	if (status == EATING)
		printf("%lld %d is eating\n", get_elapsed_time(philo->birth), philo->id);
	else if (status == SLEEPING)
		printf("%lld %d is sleeping\n", get_elapsed_time(philo->birth), philo->id);
	else if (status == THINKING)
		printf("%lld %d is thinking\n", get_elapsed_time(philo->birth), philo->id);
	else if (status == DEAD)
	{
		printf("%lld %d died\n", get_elapsed_time(philo->birth), philo->id);
		pthread_mutex_unlock(&philo->mutex);
		free_and_exit(agora, 0);
	}
	pthread_mutex_unlock(&philo->mutex);
}

// Function to get the time passed since a given event
long long	get_elapsed_time(t_timeval event)
{
	t_timeval	current_time;
	long long	ms;

	ms = 0;
	gettimeofday(&current_time, NULL);
	ms += (current_time.tv_sec - event.tv_sec) * 1000;
	ms += (current_time.tv_usec - event.tv_usec) / 1000;
	return (ms);
}