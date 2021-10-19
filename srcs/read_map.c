/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:49:03 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/14 19:59:18 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_columns(char *line, t_all *all)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			all->columnas++;
			while (line[i] >= '0' && line[i] <= '9')
				i++;
		}
		else
			i++;
	}
}

void	fill_matrix_nb(char **map, t_all *all)
{
	char	**numbers;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	while (i < all->filas)
	{
		numbers = ft_split(map[i], ' ');
		j = 0;
		while (j < all->columnas)
		{
			all->mapa[i][j] = ft_atoi(numbers[j]);
			j++;
			k++;
		}
		i++;
	}
}

void	fill_matrix(char *map, t_all *all)
{
	int	i;
	int	j;
	int	k;
	int	num;

	all->mapa = (int **)malloc(sizeof(int *) * all->filas);
	if (!all->mapa)
		exit_fdf(strerror(errno), all);
	i = 0;
	while (i < all->filas)
	{
		all->mapa[i] = (int *)malloc(sizeof(int) * all->columnas);
		if (!all->mapa)
			exit_fdf(strerror(errno), all);
		i++;
	}
	fill_matrix_nb(ft_split(map, '\n'), all);
}

void	read_map(int fd, t_all *all)
{
	char	*line;
	char	*map;
	char	*tmp;

	if (fd < 0)
		exit_fdf("Error\nCan't open map\n", all);
	map = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (map == NULL)
		{
			map = ft_strdup(line);
			check_columns(line, all);
		}
		else
		{
			tmp = special_strjoin(map, line);
			free(map);
			map = tmp;
		}
		all->filas++;
	}
	close(fd);
	fill_matrix(map, all);
}