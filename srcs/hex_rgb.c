/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:29:39 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/27 12:41:48 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		hex_to_dec(char c)
{
	if (c >= 'A' && c <= 'F')
		return (c - 55);
	if (c >= 'a' && c <= 'f')
		return (c - 87);
	return (c - 48);
}

unsigned int	get_hex(char *hex)
{
	int	rgb[3];
	int i;

	i = 0;
	while (hex[i] && hex[i] != ' ')
		i++;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	rgb[0] = 16 * hex_to_dec(hex[0]);
	rgb[0] += hex_to_dec(hex[1]);
	if (i >= 3)
	{
		rgb[1] = 16 * hex_to_dec(hex[2]);
		rgb[1] += hex_to_dec(hex[3]);
	}
	if (i >= 5)
	{
		rgb[2] = 16 * hex_to_dec(hex[4]);
		rgb[2] += hex_to_dec(hex[5]);
	}
	return (65536 * rgb[0] + 256 * rgb[1] + rgb[2]);
}

unsigned int	hexadecimal(char *map, t_all *all)
{
	int	i;

	i = 0;
	while (map[i] >= '0' && map[i] <= '9')
		i++;
	if (map[i] == ',')
	{
		i++;
		if (map[i] == '0' && map[i + 1] == 'x')
			return(get_hex(&map[i + 2]));
		else
			exit_fdf("Error, wrong map format", all);
	}
	return (0);
}
