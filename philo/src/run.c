/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/01/27 16:30:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to run the simulation
void	run_simulation(t_dclst **agora, t_rules rules, int n_threads)
{
	int			res;
	int			i;
	pthread_t	*threads;
	t_dclst		*current;

// prevoir de free threads!
	threads = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
	if (!threads)
		free_and_exit(agora, 1);
	res = pthread_create(&threads[0], NULL, survey_dead, (void *)agora);
	if (res)
		free_and_exit(agora, res);
	if (rules.nb_must_eat != -1)
	{
		res = pthread_create(&threads[n_threads - 1], NULL, survey_win, (void *)agora);
		if (res)
			free_and_exit(agora, res);
	}
	current = *agora;
	i = 1;
	while(i <= rules.nb_philo)
	{
		res = pthread_create(&threads[i], NULL, philosopher_life, (void *)current);
		if (res)
			free_and_exit(agora, res);
		current = current->next;
		i++;
	}
}

void	philosopher_life(t_dclst **agora, t_philo *philo, t_rules rules)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		philo->status = THINKING;
		write_log(agora, philo, philo->status);
		philo->status = EATING;
		write_log(agora, philo, philo->status);
		usleep(rules.time_to_eat * 1000);
		philo->status = SLEEPING;
		write_log(agora, philo, philo->status);
		usleep(rules.time_to_sleep * 1000);
		i++;
	}
}

// Function to write logs
void	write_log(t_dclst **agora, t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->mutex);
	if (status == FORK)
		printf("%lld %d has taken a fork\n", get_elapsed_time(philo->birth), philo->id);
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
