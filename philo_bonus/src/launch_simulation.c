/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/08 12:54:42 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

// Function to create the forks, create the threads and run the simulation
void	launch_simu(t_dclst **agora, t_rules *rules)
{
	pid_t		*philos_pid;
	pid_t		survey_pid;

	survey_pid = 0;
	philos_pid = (pid_t *) malloc(sizeof(pid_t) * rules->nb_philo);
	if (!philos_pid)
		error("Malloc failed", rules, agora);
	if (rules->nb_must_eat != -1)
		create_survey_process(&survey_pid, agora, rules);
	create_philo_processes(philos_pid, agora, rules, survey_pid);
	sem_wait(rules->end_sem);
	kill_processes(philos_pid, rules->nb_philo);
	if (rules->nb_must_eat != -1)
		kill(survey_pid, SIGTERM);
	free(philos_pid);
	free_and_exit(rules, agora, 0);
}

// Function to create the survey process
void	create_survey_process(pid_t *pid, t_dclst **agora, t_rules *rules)
{
	*pid = fork();
	if (*pid < 0)
		error("fork failed", rules, agora);
	if (*pid == 0)
	{
		survey_win(rules);
		exit(0);
	}
}

// Function to create the processes
void	create_philo_processes(pid_t *pid, t_dclst **agora, t_rules *rules, pid_t survey_pid)
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
			if (survey_pid)
				kill(survey_pid, SIGTERM);
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
void	kill_processes(pid_t *pid, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		kill(pid[i], SIGTERM);
		i++;
	}
}

// Function to write logs
void	write_log(t_philo *philo, int status)
{
	if (status == WON)
		printf(GREEN "%lld All philosophers have eaten enough" RESET "\n", get_actual_time());
	else if (status == DEAD)
		printf(RED "%lld %d died" RESET "\n", get_actual_time(), philo->id);
	else if (status == FORK)
		printf(GRAY "%lld %d has taken a fork" RESET "\n", get_actual_time(), philo->id);
	else if (status == EAT)
		printf(YELLOW "%lld %d is eating" RESET "\n", get_actual_time(), philo->id);
	else if (status == SLEEP)
		printf(BLUE "%lld %d is sleeping" RESET "\n", get_actual_time(), philo->id);
	else if (status == THINK)
		printf(CYAN "%lld %d is thinking" RESET "\n", get_actual_time(), philo->id);
}
