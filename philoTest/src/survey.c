/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:39:36 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/30 06:54:14 by christophed      ###   ########.fr       */
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
	int			run;

	agora = (t_dclst **) arg;
	current = *agora;
	philo = (t_philo *) current->data;
	time = philo->rules->time_to_die;
	run = access_run_thread(philo->rules, READ, 0);
	while (run)
	{
		if (get_elapsed_time(philo->last_meal) > time)
        {
			bad_end(philo);
			return (NULL);
        }
		current = current->next;
		philo = (t_philo *) current->data;
		run = access_run_thread(philo->rules, READ, 0);
	}
	return (NULL);
}

// Function to survey if all philosophers have eaten enough
void	*survey_win(void *arg)
{
	t_dclst	**agora;
	t_dclst	*current;
	t_philo	*philo;
	int		run;

	agora = (t_dclst **) arg;
	current = *agora;
	philo = (t_philo *) current->data;
	run = access_run_thread(philo->rules, READ, 0);
    while (run)
	{
		philo = (t_philo *) current->data;
		if (philo->n_meals >= philo->rules->nb_must_eat)
			if (have_won(current, philo->rules))
			{
				happy_end(philo);
				return (NULL);
			}
		current = current->next;
		run = access_run_thread(philo->rules, READ, 0);
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
