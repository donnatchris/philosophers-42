/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/25 05:54:57 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// bressenham

// LINUX compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -lX11 -lXext -lm
// avec la libft:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft -lft -lX11 -lXext -lm

// MAC compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft/includes -lft -L/opt/homebrew/opt/libx11/lib -I/opt/homebrew/opt/libx11/include -L/opt/homebrew/opt/libxext/lib -I/opt/homebrew/opt/libxext/include -lX11 -lXext -lm -framework OpenGL -framework AppKit

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_point	**point;
	t_fdf	*fdf;
	
	errno = 0;
	if (ac != 2)
		error("Wrong number of arguments");
	point = read_and_extract(av[1]);
	fdf = malloc_fdf();
	if (!fdf)
		return (ft_printf("memory allocation failed"),1);
	init_fdf(fdf, point);
	printf("x_max = %f, y_max = %f, z_max = %f\n", fdf->x_max, fdf->y_max, fdf->z_max);
	// project_isometric_map(fdf);
	// draw_lines(fdf);
	// print_menu(fdf);
	// mlx_hook(fdf->win_ptr, 2, 1L << 0, deal_key, fdf);
	// mlx_hook(fdf->win_ptr, 17, 0L, free_and_exit, fdf);
	// mlx_loop_hook(fdf->mlx_ptr, render, fdf);
	// mlx_loop(fdf->mlx_ptr);
	return (0);
}

