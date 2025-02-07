/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:55:03 by christophed       #+#    #+#             */
/*   Updated: 2025/02/07 20:33:17 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	t_dclst	**agora;

	if (ac != 5 && ac != 6)
		error("Invalid number of arguments", NULL, NULL);
	store_rules(&rules, ac, av);
	print_rules(rules);
	agora = malloc(sizeof(t_dclst *));
	if (!agora)
		error("malloc failed", &rules, NULL);
	store_philosophers(agora, rules.nb_philo, &rules);
	launch_simu(agora, &rules);
	return (0);
}
