/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:57:15 by christophed       #+#    #+#             */
/*   Updated: 2025/02/10 13:16:04 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	rules = ((t_philo *) current->data)->rules;
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

// Function to survey if all philosophers have eaten enough
void	*survey_win(void *arg)
{
	t_dclst	**agora;
	t_dclst	*current;
	t_philo	*philo;
	t_rules	*rules;

	agora = (t_dclst **) arg;
	current = *agora;
	rules = ((t_philo *) current->data)->rules;
	while (check_run(rules, READ))
	{
		philo = (t_philo *) current->data;
		if (check_n_meals(philo, READ) >= philo->rules->nb_must_eat)
		{
			if (have_won(current, philo->rules))
			{
				write_log(philo, WON);
				return (NULL);
			}
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
