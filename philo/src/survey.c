/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:39:36 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/27 15:28:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to survey if a philosopher is dead
void	survey_dead(t_dclst **agora, t_rules rules)
{
	t_dclst	*current;
	t_philo	*philo;

	current = *agora;
	philo = current->data;
	while (1)
	{
		if (get_elapsed_time(philo->last_meal) > rules.time_to_die)
        {
			write_log(agora, philo, DEAD);
			free_and_exit(agora, 0);
        }
		current = current->next;
		philo = current->data;
	}
}

// Function to survey if all philosophers have eaten enough
void	survey_win(t_dclst **agora, t_rules rules)
{
	t_dclst	*current;
	t_philo	*philo;

	current = *agora;
	philo = current->data;
	while (1)
	{
		if (philo->n_meals >= rules.nb_must_eat)
			if (have_won(current, rules))
			{
				printf("All philosophers have eaten enough!\n");
				free_and_exit(agora, 0);
			}
		current = current->next;
		philo = current->data;
	}
}

// Function to check if other philosophers have eaten enough
int	have_won(t_dclst *current, t_rules rules)
{
	t_philo	*philo;
	int		i;

	philo = current->data;
	i = 0;
	while(i < rules.nb_must_eat)
	{
		if (philo->n_meals < rules.nb_must_eat)
			break ;
		i++;
		current = current->next;
		philo = current->data;
	}
	if (i < rules.nb_philo)
		return (0);
	return (1);
}