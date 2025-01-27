/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:55:03 by christophed       #+#    #+#             */
/*   Updated: 2025/01/27 15:44:53 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	t_dclst	**agora;
	int		n_threads;

	store_input(&rules, ac, av);
	print_rules(rules);
	agora = NULL;
	agora = malloc(sizeof(t_dclst *));
	if (!agora)
		error("Malloc failed", NULL);
	store_philosophers(agora, rules.nb_philo);
	if (rules.nb_must_eat == -1)
		n_threads = rules.nb_philo + 1;
	else
		n_threads = rules.nb_philo + 2;
	run_simulation(agora, rules, n_threads);
	free_and_exit(agora, 0);
	return (0);
}

