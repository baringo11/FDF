/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:49:03 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/27 19:01:35 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_line(char *line, t_all *all)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			all->filas++;
			return ;
		}
		i++;
	}
}

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
		else if (line[i] == ',')
		{
			while (line[i] && line[i] != ' ')
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
			all->hex_color[i][j] = hexadecimal(numbers[j], all);
			all->mapa[i][j] = ft_atoi(numbers[j]);
			j++;
			k++;
		}
		ft_free_matrix(numbers);
		i++;
	}
	ft_free_matrix(map);
}

void	fill_matrix(char *map, t_all *all, int fd)
{
	int		i;
	char	**mapa;

	close(fd);
	all->mapa = (int **)malloc(sizeof(int *) * all->filas);
	all->hex_color = (unsigned int **)malloc(sizeof(unsigned int *) * all->filas);
	if (!all->mapa || !all->hex_color)
		exit_fdf(strerror(errno), all);
	i = 0;
	while (i < all->filas)
	{
		all->mapa[i] = (int *)malloc(sizeof(int) * all->columnas);
		all->hex_color[i] = (unsigned int *)malloc(sizeof(unsigned int) * all->columnas);
		if (!all->mapa[i] || !all->hex_color[i])
			exit_fdf(strerror(errno), all);
		i++;
	}
	mapa = ft_split(map, '\n');
	free(map);
	map = NULL;
	fill_matrix_nb(mapa, all);
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
			check_columns(line, all);
			map = ft_strdup(line);
		}
		else
		{
			tmp = special_strjoin(map, line);
			free(map);
			map = tmp;
		}
		check_line(line, all);
		free(line);
	}
	free(line);
	fill_matrix(map, all, fd);
}
