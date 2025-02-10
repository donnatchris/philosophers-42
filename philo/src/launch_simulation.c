/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/10 13:13:27 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to create the forks, create the threads and run the simulation
void	launch_simu(t_dclst **agora, t_rules *rules)
{
	pthread_t	*threads;
	int			n_threads;

	n_threads = rules->nb_philo + 1;
	if (rules->nb_must_eat != -1)
		n_threads++;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
	if (!threads)
		error("malloc failed", rules, agora);
	create_threads(agora, rules, threads);
	join_threads(threads, n_threads);
	free(threads);
	free_and_exit(rules, agora, 0);
}

// Function to create the threads
void	create_threads(t_dclst **agora, t_rules *rules, pthread_t *threads)
{
	int		res;
	int		i;
	t_dclst	*current;

	res = 0;
	res += pthread_create(&threads[0], NULL, survey_dead, (void *)agora);
	if (rules->nb_must_eat != -1)
		res += pthread_create(&threads[rules->nb_philo + 1], \
		NULL, survey_win, (void *)agora);
	current = *agora;
	i = 1;
	while (i <= rules->nb_philo)
	{
		res += pthread_create(&threads[i], NULL, philosopher_life, \
		(void *)current);
		current = current->next;
		i++;
	}
	if (res)
	{
		check_run(rules, STOP);
		free(threads);
		error("pthread error", rules, agora);
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
