/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:48:45 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/19 19:08:22 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	put_pixel(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = all->mlx.data + (y * all->mlx.size_line + x * (all->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_legend(t_all *all)
{
	int		y;

	y = 0;
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 20, 0xffffff, \
	"HOW TO USE");
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 25, 0xff00ff, \
	"Color: 'C' Key");
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 25, 0xff00ff, \
	"Zoom: Scroll Mouse");
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 25, 0xff00ff, \
	"Move: Click and Move");
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 25, 0xff00ff, \
	"Altitude: 'W' and 'S' Keys");
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 25, 0xff00ff, \
	"Rotate: 'A' and 'D' Keys");
	mlx_string_put(all->mlx.init, all->mlx.win, 15, y += 25, 0xff00ff, \
	"Projections: SPACE key");
}

void	pre_algorithm(float x, float y, int flag, t_all *all)
{
	t_points	points;

	points.x = x;
	points.y = y;
	if (flag)
	{
		points.x1 = x + 1;
		points.y1 = y;
	}
	else
	{
		points.x1 = x;
		points.y1 = y + 1;
	}
	algorithm(points, all);
}

void	draw(t_all *all)
{
	int	x;
	int	y;

	new_wind(all);
	y = 0;
	while (y < all->filas)
	{
		x = 0;
		while (x < all->columnas)
		{
			if (x < all->columnas - 1)
				pre_algorithm(x, y, 1, all);
			if (y < all->filas - 1)
				pre_algorithm(x, y, 0, all);
			x++;
		}
		y++;
	}
	mlx_clear_window(all->mlx.init, all->mlx.win);
	mlx_put_image_to_window(all->mlx.init, all->mlx.win, all->mlx.image, 0, 0);
	draw_legend(all);
}
