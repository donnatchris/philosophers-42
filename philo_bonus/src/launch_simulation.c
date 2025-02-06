/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 15:25:46 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to create the forks, create the threads and run the simulation
void	launch_simu(t_dclst **agora, t_rules rules)
{
	pid_t	*pid;

	pid = (pid_t *) malloc(sizeof(pid_t) * rules.nb_philo);
	if (!pid)
		error("Malloc failed", &rules, agora);
	create_processes(pid, agora, &rules);
	
	join_threads(threads, n_threads);
	free(pid);
	free_and_exit(&rules, agora, 0);
}

// Function to create the threads
void	create_processes(pid_t *pid, t_dclst **agora, t_rules *rules)
{
	int		i;
	t_philo	philo;

	philo = (t_philo *)
	i = 0;
	while (i < rules->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			while (pid[--i])
				kill(pid[i], SIGTERM);
			error("fork failed", rules, agora);
		}
		if (pid[i] == 0)
			philosopher_life(agora[i]);
		else
			i++;
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
	while (i < rules->nb_philo)
	{
		philo = (t_philo *) current->data;
		if (check_n_meals(philo, READ) < rules->nb_must_eat)
			return (0);
		i++;
		current = current->next;
	}
	return (1);
}
