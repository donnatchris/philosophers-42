/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:07:17 by christophed       #+#    #+#             */
/*   Updated: 2025/02/07 22:02:41 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to check if all philosophers have eaten enough
void	*survey_win(void *arg)
{
	t_dclst	*current;
	t_philo	*philo;
	t_rules *rules;
	int		has_finished;

	current = (t_dclst *) arg;
	philo = (t_philo *) current->data;
	rules = philo->rules;
	has_finished = 0;
	while (1)
	{
		sem_wait(rules->win_sem);
		has_finished++;
		if (has_finished == rules->nb_philo)
		{
			sem_wait(rules->log_sem);
			write_log(philo, WON);
			sem_post(rules->end_sem);
			break ;
		}
	}
	return (NULL);
}

// Function to survey if a philosopher is dead
void	*survey_dead(void *arg)
{
	int		time;
	t_philo	*philo;

	philo = (t_philo *) arg;
	time = philo->rules->time_to_die;
	while (check_stop_thread(philo->rules, READ) == 0)
	{
		if (get_elapsed_time(check_last_meal(philo, READ)) > time)
		{
			sem_wait(philo->rules->log_sem);
			write_log(philo, DEAD);
			sem_post(philo->rules->end_sem);
			break ;
		}
	}
	return (NULL);
}

// Function to check or modify last_meal variable
long long	check_last_meal(t_philo *philo, int mode)
{
	long long	last_meal;

	sem_wait(philo->last_meal_sem);
	if (mode == WRITE)
		philo->last_meal = get_actual_time();
	last_meal = philo->last_meal;
	sem_post(philo->last_meal_sem);
	return (last_meal);
}

int	check_stop_thread(t_rules *rules, int mode)
{
	int	stop_thread;

	sem_wait(rules->stop_thread_sem);
	if (mode == STOP)
		rules->stop_thread = 1;
	stop_thread = rules->stop_thread;
	sem_post(rules->stop_thread_sem);
	return (stop_thread);
}