/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 20:40:53 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to print an error message and free the agora list
void	error(char *message, t_dclst **agora)
{
	if (agora)
		dclst_clear(agora);
	printf("Error: %s\n", message);
	exit(1);
}

// Function to print the death of a philosopher
void	print_dead(int	id)
{
	printf("Philosopher %d died\n", id);
	printf("x_x\n");
}
