/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:12:34 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 05:42:32 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Free the memory allocated for a table of t_points
void	free_points_tab(t_point **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

// Free the memory allocated for a table of strings
void	free_str_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

// Function to free allocated memory before exiting
int	free_and_exit(t_fdf *fdf)
{
	free_fdf(fdf);
	exit (1);
}

// Function to free the memory allocated for the fdf structure on Linux
void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->point)
		{
			free_points_tab(fdf->point);
			fdf->point = NULL;
		}
		if (fdf->img_ptr)
		{
			mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
			fdf->img_ptr = NULL;
		}
		if (fdf->win_ptr)
		{
			mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
			fdf->win_ptr = NULL;
		}
		if (fdf->mlx_ptr)
		{
			// mlx_destroy_display(fdf->mlx_ptr);
			free(fdf->mlx_ptr);
			fdf->mlx_ptr = NULL;
		}
		free(fdf);
		fdf = NULL;
	}
}


// Function to free multiple pointers
// void	multiple_free(int count, ...)
// {
// 	va_list	args;
// 	void	*ptr;
// 	int		i;

// 	va_start(args, count);
// 	i = 0;
// 	while (i < count)
// 	{
// 		ptr = va_arg(args, void *);
// 		free(ptr);
// 		i++;
// 	}
// 	va_end(args);
// }