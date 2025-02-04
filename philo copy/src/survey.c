/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:39:36 by chdonnat          #+#    #+#             */
/*   Updated: 2025/02/04 14:33:42 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to survey if a philosopher is dead
void	*survey_dead(void *arg)
{
	t_dclst		**agora;
	t_dclst		*current;
	t_philo		*philo;
	int			time;

	agora = (t_dclst **) arg;
	current = *agora;
	philo = (t_philo *) current->data;
	time = philo->rules->time_to_die;
	while (philo->rules->run_threads)
	{
		if (get_elapsed_time(philo->last_meal) > time)
        {
			write_log(philo, DEAD);
			return (NULL);
        }
		current = current->next;
		philo = (t_philo *) current->data;
	}
	return (NULL);
}

// Function to survey if all philosophers have eaten enough
void	*survey_win(void *arg)
{
	t_dclst		**agora;
	t_dclst	*current;
	t_philo	*philo;

	agora = (t_dclst **) arg;
	current = *agora;
    while (((t_philo *) current->data)->rules->run_threads)
	{
		philo = (t_philo *) current->data;
		if (philo->n_meals >= philo->rules->nb_must_eat)
			if (have_won(current, philo->rules))
			{
				write_log(philo, WON);
				return (NULL);
			}
		current = current->next;
	}
	return (NULL);
}

// Function to check if other philosophers have eaten enough
int	have_won(t_dclst *current, t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while(i < rules->nb_philo)
	{
		philo = (t_philo *) current->data;
		if (philo->n_meals < rules->nb_must_eat)
			return (0);
		i++;
		current = current->next;
	}
	return (1);
}

// Function to check or modify run_threads variable
int	check_run(t_rules *rules, int mode)
{
	int	run;

	pthread_mutex_lock(&rules->run_mutex);
	if (mode == STOP)
		rules->run_threads = 0;
	run = rules->run_threads;
	pthread_mutex_unlock(&rules->run_mutex);
	return (run);
}
