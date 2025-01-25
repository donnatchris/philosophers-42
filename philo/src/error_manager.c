/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:47:40 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 23:00:33 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to exit the program and free memory
void	free_and_exit(t_dclst **agora, int status)
{
	if (agora)
		dclst_clear(agora);
	exit(status);
}

// Function to print an error message and free the agora list
void	error(char *message, t_dclst **agora)
{
	printf("Error: %s\n", message);
	free_and_exit(agora, 1);
}

// Function to print the death of a philosopher
void	print_dead(int	id)
{
	printf("Philosopher %d died\n", id);
	printf("x_x\n");
}
