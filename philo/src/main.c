/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:55:03 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 20:45:44 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	t_dclst	**agora;

	store_input(&rules, ac, av);
	print_rules(rules);
	agora = NULL;
	agora = malloc(sizeof(t_dclst *));
	if (!agora)
		error("Malloc failed", NULL);
	store_philosophers(agora, rules.nb_philo);
	error("End of program", agora);
	return (0);
}

