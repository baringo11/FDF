/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:49:06 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/27 18:38:12 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	rgb_progressive(int i, int initial_c, int final_c, int n)
{
	if (n > 0)
		return (initial_c + (i * (final_c - initial_c) / n));
	return (0);
}

int	choose_color(float z, float z1, unsigned int *color, t_all *all)
{
	if (all->color == 0 && *color == 0)
		*color = 0x7CFF00;
	if (all->color != 0)
		*color = 0xFFFFFF;
	if (all->color > 0)
	{
		if (z > 0 && z1 > 0)
			*color = 0xFF0000;
		else if (z < 0 && z1 <= 0)
			*color = 0x00FF00;
		if (z > z1 && z1 == 0)
			return (2);
		if (z1 > z && z == 0)
			return (3);
		if (z > z1 && z == 0 && z1 < 0)
			return (4);
		if (z1 > z && z1 == 0 && z < 0)
			return (5);
		if (z > 0 && z1 < 0)
			return (6);
		if (z < 0 && z1 > 0)
			return (7);
		return (1);
	}
	return (all->color);
}

unsigned int	get_color(int i, int n, t_all *all)
{
	if (all->color == 2)
		return (65536 * rgb_progressive(i, 255, 0, n) + 256 * \
		rgb_progressive(i, 0, 0, n) + rgb_progressive(i, 0, 255, n));
	else if (all->color == 3)
		return (65536 * rgb_progressive(i, 0, 255, n) + 256 * \
		rgb_progressive(i, 0, 0, n) + rgb_progressive(i, 255, 0, n));
	else if (all->color == 4)
		return (65536 * rgb_progressive(i, 0, 0, n) + 256 * \
		rgb_progressive(i, 0, 255, n) + rgb_progressive(i, 255, 0, n));
	else if (all->color == 5)
		return (65536 * rgb_progressive(i, 0, 0, n) + 256 * \
		rgb_progressive(i, 255, 0, n) + rgb_progressive(i, 0, 255, n));
	else if (all->color == 6 && i <= (n / 2))
		return (65536 * rgb_progressive(i, 255, 0, n / 2) + 256 * \
		rgb_progressive(i, 0, 0, n / 2) + rgb_progressive(i, 0, 255, n / 2));
	else if (all->color == 6 && i >= (n / 2))
		return (65536 * rgb_progressive(i, 0, 0, n / 2) + 256 * \
		rgb_progressive(i, 0, 255, n / 2) + rgb_progressive(i, 255, 0, n / 2));
	else if (all->color == 7 && i <= (n / 2))
		return (65536 * rgb_progressive(i, 0, 0, n / 2) + 256 * \
		rgb_progressive(i, 255, 0, n / 2) + rgb_progressive(i, 0, 255, n / 2));
	else if (all->color == 7 && i >= (n / 2))
		return (65536 * rgb_progressive(i, 0, 255, n) + 256 * \
		rgb_progressive(i, 0, 0, n) + rgb_progressive(i, 255, 0, n));
	return (0);
}
