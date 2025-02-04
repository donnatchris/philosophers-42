/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 14:34:09 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to create the threads and run the simulation
void	run_simulation(t_dclst **agora, t_rules rules, int n_threads)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
	if (!threads)
		free_and_exit(agora, 1);
	create_threads(agora, rules, threads, n_threads);
	join_threads(threads, n_threads);
	free(threads);
	free_and_exit(agora, 0);
}

// Function to create the threads
void	create_threads(t_dclst **agora, t_rules rules, \
	pthread_t *threads, int n_threads)
{
	int		res;
	int		i;
	t_dclst	*current;

	res = 0;
	res += pthread_create(&threads[0], NULL, survey_dead, (void *)agora);
	if (rules.nb_must_eat != -1)
		res += pthread_create(&threads[n_threads - 1], NULL, \
			survey_win, (void *)agora);
	current = *agora;
	i = 1;
	while (i <= rules.nb_philo)
	{
		res += pthread_create(&threads[i], NULL, philosopher_life, \
		(void *)current);
		current = current->next;
		i++;
	}
	if (res)
	{
		((t_philo *)(*agora)->data)->rules->run_threads = 0;
		free(threads);
		error("pthread error", agora);
	}
}

// Function to join the threads
void	join_threads(pthread_t *threads, int n_threads)
{
	int	i;

	i = 0;
	while (i < n_threads)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

// Function to write logs
void	write_log(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->rules->log_mutex);
	if (check_run(philo->rules, READ))
	{
		if (status == WON)
		{
			check_run(philo->rules, STOP);
			printf("%lld All philosophers have eaten enough\n", get_actual_time());
		}
		else if (status == DEAD)
		{
			check_run(philo->rules, STOP);
			printf("%lld %d died\n", get_actual_time(), philo->id);
		}
		else if (status == FORK)
			printf("%lld %d has taken a fork\n", get_actual_time(), philo->id);
		else if (status == EAT)
			printf("%lld %d is eating\n", get_actual_time(), philo->id);
		else if (status == SLEEP)
			printf("%lld %d is sleeping\n", get_actual_time(), philo->id);
		else if (status == THINK)
			printf("%lld %d is thinking\n", get_actual_time(), philo->id);
	}
	pthread_mutex_unlock(&philo->rules->log_mutex);
}
