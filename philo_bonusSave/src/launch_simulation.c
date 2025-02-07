/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 19:20:04 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to create the forks, create the threads and run the simulation
void	launch_simu(t_dclst **agora, t_rules *rules)
{
	pid_t	*pid;
	int		i;

	pid = (pid_t *) malloc(sizeof(pid_t) * rules->nb_philo);
	if (!pid)
		error("Malloc failed", rules, agora);
	create_processes(pid, agora, rules);
	survey_dead(agora, rules);
	i = 0;
	while (i < rules->nb_philo)
    {
        waitpid(pid[i], NULL, 0);
		i++;
    }
	free(pid);
	free_and_exit(rules, agora, 0);
}

// Function to create the processes
void	create_processes(pid_t *pid, t_dclst **agora, t_rules *rules)
{
	int		i;
	t_dclst	*current;

	current = *agora;
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
		{
			philosopher_life(current);
			exit(0);
		}
		i++;
		current = current->next;
	}
}

// Function to kill all the child processes
void	kill_processes(pid_t *pid, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		kill(pid[i], SIGTERM);
		i++;
	}
}

// Function to survey if a philosopher is dead
void	survey_dead(t_dclst **agora, t_rules *rules)
{
	t_dclst		*current;
	t_philo		*philo;
	int			time;

	current = *agora;
	philo = (t_philo *) current->data;
	time = philo->rules->time_to_die;
	while (1)
	{
		if (get_elapsed_time(check_last_meal(philo, READ)) > time)
		{
			write_log(philo, DEAD);
			return ;
		}
		if (philo->rules->nb_must_eat != -1)
			if (check_n_meals(philo, READ) >= philo->rules->nb_must_eat)
				if (check_victory(*agora, rules))
				{
					write_log(philo, WON);
					return ;
				}
		current = current->next;
		philo = (t_philo *) current->data;
	}
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
