/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:17:03 by christophed       #+#    #+#             */
/*   Updated: 2025/01/22 11:10:37 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Count the number of columns in the first line of a file
int	count_columns(char *file)
{
	int		fd;
	char	*line;
	char 	**tab;
	int		n_columns;
	
	n_columns = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		close_fd_and_error(fd, "Error opening file");
	line = get_next_line(fd);
	if (!line)
		close_fd_and_error(fd, "Error reading file");
	tab = ft_split(line, ' ');
	if (!tab)
	{
		free(line);
		close_fd_and_error(fd, "Error splitting line");
	}
	while (tab[n_columns])
		n_columns++;
	free_str_tab(tab);
	free (line);
	close(fd);
	return (n_columns);
}

// Count the number of lines in a file
int	count_lines(char *file)
{
	int		fd;
	int		n_lines;
	char	*line;

	n_lines = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		close_fd_and_error(fd, "Error opening file");
	line = get_next_line(fd);
	while (line)
	{
		n_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (n_lines);
}

// Function to find the maximum x value among the points
int	find_x_max(t_fdf *fdf)
{
	int i;
	int x_max;

	i = 0;
	x_max = 0;
	while (fdf->point[i])
	{
		if (fdf->point[i]->x > x_max)
			x_max = fdf->point[i]->x;
		i++;
	}
	return (x_max);
}

// Function to find the maximum y value among the points
int	find_y_max(t_fdf *fdf)
{
	int i;
	int y_max;

	i = 0;
	y_max = 0;
	while (fdf->point[i])
	{
		if (fdf->point[i]->y > y_max)
			y_max = fdf->point[i]->y;
		i++;
	}
	return (y_max);
}

// Function to find the maximum z value among the points
int	find_z_max(t_fdf *fdf)
{
	int i;
	int z_max;

	i = 0;
	z_max = 0;
	while (fdf->point[i])
	{
		if (fdf->point[i]->z > z_max)
			z_max = fdf->point[i]->z;
		i++;
	}
	return (z_max);
}
