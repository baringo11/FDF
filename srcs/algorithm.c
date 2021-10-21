/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:35:56 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/21 13:02:02 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	projections(float *x, float *y, float z, t_all *all)
{
	if (all->projection == 1)
	{
		*x = (*x - *y) * cos(1);
		*y = (*x + *y) * sin(1) - z;
	}
	else if (all->projection == 2)
	{
		*x = (*x + *y) * cos(0);
		*y = (*y - *x) - z;
	}
}

void	rotation(float *x, float *y, t_all *all)
{
	float	x1;

	x1 = *x * cos(all->axis_z_rotation) - *y * sin(all->axis_z_rotation);
	*y = *x * sin(all->axis_z_rotation) + *y * cos(all->axis_z_rotation);
	*x = x1;
}

int	number_of_colors(float x, float x1, float y, float y1)
{
	int		i;
	int		max;
	float	x_step;
	float	y_step;

	x_step = x1 - x;
	y_step = y1 - y;
	max = (int)max_nb(normalize(x_step), normalize(y_step));
	x_step /= max;
	y_step /= max;
	i = 0;
	while ((int)(x - x1) || (int)(y - y1))
	{
		i++;
		x += x_step;
		y += y_step;
	}
	return (i);
}

void	algorithm2(t_points points, int color, t_all *all)
{
	float	x_step;
	float	y_step;
	int		max;
	int		n;
	int		i;

	x_step = points.x1 - points.x;
	y_step = points.y1 - points.y;
	max = (int)max_nb(normalize(x_step), normalize(y_step));
	x_step /= max;
	y_step /= max;
	n = number_of_colors(points.x, points.x1, points.y, points.y1);
	i = 0;
	while ((int)(points.x - points.x1) || (int)(points.y - points.y1))
	{
		if (all->color > 1)
			color = get_color(i, n, all);
		i++;
		if (points.x >= 0 && points.x < WIDTH && \
			points.y >= 0 && points.y < HEIGHT)
			put_pixel(all, points.x, points.y, color);
		points.x += x_step;
		points.y += y_step;
	}
}

void	algorithm(t_points points, t_all *all)
{
	float	z;
	float	z1;
	int		color;

	z = all->mapa[(int)points.y][(int)points.x];
	z1 = all->mapa[(int)points.y1][(int)points.x1];
	z *= all->altitude;
	z1 *= all->altitude;
	all->color = choose_color(z, z1, &color, all);
	rotation(&points.x, &points.y, all);
	rotation(&points.x1, &points.y1, all);
	projections(&points.x, &points.y, z, all);
	projections(&points.x1, &points.y1, z1, all);
	points.x *= all->zoom;
	points.x1 *= all->zoom;
	points.y *= all->zoom;
	points.y1 *= all->zoom;
	points.x += all->shift_x;
	points.x1 += all->shift_x;
	points.y += all->shift_y;
	points.y1 += all->shift_y;
	algorithm2(points, color, all);
}
