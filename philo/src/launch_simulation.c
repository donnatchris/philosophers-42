/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 17:11:09 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to create the forks, create the threads and run the simulation
void	launch_simu(t_dclst **agora, t_rules rules)
{
	pthread_t	*threads;
	int			n_threads;

	n_threads = rules.nb_philo + 1;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
	if (!threads)
		free_and_exit(agora, 1);
	create_threads(agora, rules, threads);
	join_threads(threads, n_threads);
	free(threads);
	free_and_exit(agora, 0);
}

// Function to create the threads
void	create_threads(t_dclst **agora, t_rules rules, pthread_t *threads)
{
	int		res;
	int		i;
	t_dclst	*current;

	res = 0;
	res += pthread_create(&threads[0], NULL, survey_dead, (void *)agora);
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
		check_run(&rules, STOP);
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

// Function to survey if a philosopher is dead
void	*survey_dead(void *arg)
{
	t_dclst		**agora;
	t_dclst		*current;
	t_rules		*rules;
	t_philo		*philo;
	int			time;

	agora = (t_dclst **) arg;
	current = *agora;
	rules = ((t_philo *)current->data)->rules;
	philo = (t_philo *) current->data;
	time = philo->rules->time_to_die;
	while (check_run(rules, READ))
	{
		if (get_elapsed_time(check_last_meal(philo, READ)) > time)
        {
			write_log(philo, DEAD);
			return (NULL);
        }
		current = current->next;
		philo = (t_philo *) current->data;
	}
	return (NULL);
}

// Function to check if all philosophers have eaten enough
int	check_victory(t_dclst *current, t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while(i < rules->nb_philo)
	{
		philo = (t_philo *) current->data;
		if (check_n_meals(philo, READ) < rules->nb_must_eat)
			return (0);
		i++;
		current = current->next;
	}
	return (1);
}
