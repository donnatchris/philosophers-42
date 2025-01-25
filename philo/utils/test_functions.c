/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:30:44 by christophed       #+#    #+#             */
/*   Updated: 2025/01/11 11:04:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to print a table of points
void	print_point_tab(t_point **tab)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (tab[i])
	{
		if (tab[i]->y != y)
		{
			ft_printf("\n");
			y = tab[i]->y;
		}
		ft_printf("%d ",tab[i]->z);
		i++;
	}
	ft_printf("\n");
}