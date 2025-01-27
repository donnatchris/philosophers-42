/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/01/28 00:41:14 by christophed      ###   ########.fr       */
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
void	create_threads(t_dclst **agora, t_rules rules, pthread_t *threads, int n_threads)
{
    int		res = 0;
    int		i;
    t_dclst	*current;

    res += pthread_create(&threads[0], NULL, survey_dead, (void *)agora);
    if (rules.nb_must_eat != -1)
        res += pthread_create(&threads[n_threads - 1], NULL, survey_win, (void *)agora);
    current = *agora;
    i = 1;
    while (i <= rules.nb_philo)
    {
        res += pthread_create(&threads[i], NULL, philosopher_life, (void *)current);
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
void	write_log(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->log_mutex);
	if (philo->status == FORK)
		printf("%lld %d has taken a fork\n", get_elapsed_time(philo->birth), philo->id);
	if (philo->status == EATING)
		printf("%lld %d is eating\n", get_elapsed_time(philo->birth), philo->id);
	else if (philo->status == SLEEPING)
		printf("%lld %d is sleeping\n", get_elapsed_time(philo->birth), philo->id);
	else if (philo->status == THINKING)
		printf("%lld %d is thinking\n", get_elapsed_time(philo->birth), philo->id);
	pthread_mutex_unlock(&philo->rules->log_mutex);
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
