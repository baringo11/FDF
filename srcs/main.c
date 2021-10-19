/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:48:59 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/19 18:40:28 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	new_wind(t_all *all)
{
	if (!all->mlx.init || !all->mlx.win)
	{
		all->mlx.init = mlx_init();
		all->mlx.win = mlx_new_window(all->mlx.init, WIDTH, HEIGHT, "FDF");
	}
	if (all->mlx.image)
		mlx_destroy_image(all->mlx.init, all->mlx.image);
	all->mlx.image = mlx_new_image(all->mlx.init, WIDTH, HEIGHT);
	all->mlx.data = mlx_get_data_addr(all->mlx.image, &all->mlx.bpp, \
	&all->mlx.size_line, &all->mlx.endian);
}

void	initializate_variables(t_all *all)
{
	all->mlx.init = NULL;
	all->mlx.win = NULL;
	all->mlx.image = NULL;
	all->filas = 0;
	all->columnas = 0;
	all->shift_x = 250;
	all->shift_y = 150;
	all->zoom = 15.0;
	all->altitude = 0.1;
	all->color = 1;
	all->axis_z_rotation = 0.0;
	all->projection = 1;
}

int	main(int argc, char **argv)
{
	t_all	all;

	initializate_variables(&all);
	if (argc != 2)
		exit_fdf("wrong number of parameters\n", &all);
	read_map(open(argv[1], O_RDONLY), &all);
	draw(&all);
	mlx_hook(all.mlx.win, 2, 1L << 0, &key_press, &all);
	mlx_hook(all.mlx.win, 4, 1L << 2, &mouse_press, &all);
	mlx_hook(all.mlx.win, 6, 1L << 13, &mouse_move, &all);
	mlx_hook(all.mlx.win, 17, 0, &exit_fdf, NULL);
	mlx_loop(all.mlx.init);
	return (EXIT_SUCCESS);
}

int	exit_fdf(char *error, t_all *all)
{
	if (error)
		write(1, error, ft_strlen(error));
	if (error)
	{
		if (all->mlx.image)
			mlx_destroy_image(all->mlx.init, all->mlx.image);
		if (all->mlx.win)
			mlx_destroy_window(all->mlx.init, all->mlx.win);
	}
	write(1, "** EXIT **\n", 11);
	exit(1);
}
