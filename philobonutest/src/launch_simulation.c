/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:29:43 by christophed       #+#    #+#             */
/*   Updated: 2025/02/07 22:08:50 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to create the forks, create the threads and run the simulation
void	launch_simu(t_dclst **agora, t_rules *rules)
{
	pid_t		*pid;
	// pthread_t	thread;

	pid = (pid_t *) malloc(sizeof(pid_t) * rules->nb_philo);
	if (!pid)
		error("Malloc failed", rules, agora);
	// if (pthread_create(&thread, NULL, survey_win, agora) != 0)
	// {
	// 	free(pid);
	// 	error("pthread_create failed", rules, agora);
	// }
	// if (pthread_detach(thread) != 0)
	// {
	// 	free(pid);
	// 	error("pthread_detach failed", rules, agora);
	// }
	create_processes(pid, agora, rules);
	sem_wait(rules->end_sem);
	// check_stop_thread(rules, STOP);
	kill_processes(pid, rules->nb_philo);
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
		printf(GREEN "%lld All philosophers have eaten enough" RESET "\n", \
			get_actual_time());
	else if (status == DEAD)
		printf(RED "%lld %d died" RESET "\n", get_actual_time(), philo->id);
	else if (status == FORK)
		printf("%lld %d has taken a fork\n", get_actual_time(), philo->id);
	else if (status == EAT)
		printf("%lld %d is eating\n", get_actual_time(), philo->id);
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n", get_actual_time(), philo->id);
	else if (status == THINK)
		printf("%lld %d is thinking\n", get_actual_time(), philo->id);
}
