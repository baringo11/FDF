/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:48:52 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/27 18:39:25 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	key_press2(int keycode, t_all *all)
{
	if (keycode == KEY_COLOR_C)
	{
		if (all->color > 0)
			all->color = -1;
		else if (all->color == 0)
			all->color = 1;
		else
			all->color = 0;
	}
	if (keycode == KEY_PROJECTION_SPACE)
	{
		if (all->projection < 3)
			all->projection++;
		else
			all->projection = 1;
		all->axis_z_rotation = 0.0;
		if (all->projection == 2)
			all->axis_z_rotation = 1.57;
		all->zoom = 15.0;
		all->altitude = 0.10;
		all->shift_x = 250;
		all->shift_y = 150;
	}
	return (0);
}

int	key_press(int keycode, t_all *all)
{
	if (keycode == KEY_UP_ARROW)
		all->shift_y += 20;
	if (keycode == KEY_DOWN_ARROW)
		all->shift_y -= 20;
	if (keycode == KEY_LEFT_ARROW)
		all->shift_x += 20;
	if (keycode == KEY_RIGHT_ARROW)
		all->shift_x -= 20;
	if (keycode == KEY_ESC)
		exit_fdf("", all);
	if (keycode == KEY_ZOOM_IN)
		all->zoom += 1;
	if (keycode == KEY_ZOOM_OUT)
		all->zoom -= 1;
	if (keycode == KEY_ALTITUDE_W)
		all->altitude += 0.1;
	if (keycode == KEY_ALTITUDE_S)
		all->altitude -= 0.1;
	if (keycode == KEY_ROTATE_D)
		all->axis_z_rotation -= 0.1;
	if (keycode == KEY_ROTATE_A)
		all->axis_z_rotation += 0.1;
	key_press2(keycode, all);
	draw(all);
	return (0);
}

int	mouse_move(int x, int y, t_all *all)
{
	if (all->mouse_flag)
	{
		if (x < all->x_cord)
			all->shift_x -= 8;
		if (x > all->x_cord)
			all->shift_x += 8;
		if (y < all->y_cord)
			all->shift_y -= 8;
		if (y > all->y_cord)
			all->shift_y += 8;
		all->x_cord = x;
		all->y_cord = y;
		draw(all);
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_all *all)
{
	all->x_cord = x;
	all->y_cord = y;
	if (button == 1)
		all->mouse_flag = 1;
	else if (button == 4)
	{
		all->zoom++;
		if (all->zoom < 1000)
			all->zoom *= 1.2;
	}
	else if (button == 5)
		all->zoom *= 0.66666;
	if (button == 4 || button == 5)
		draw(all);
	return (0);
}

int	mouse_release(int button, int x, int y, t_all *all)
{
	x++;
	y++;
	button++;
	all->mouse_flag = 0;
	return (0);
}
