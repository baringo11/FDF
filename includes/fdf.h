/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:23:57 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/27 19:17:48 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <math.h>

# include "../srcs/GNL/get_next_line.h"
# include "../srcs/minilibx_macos/mlx.h"

# define WIDTH 800
# define HEIGHT 700

# define KEY_ESC 53
# define KEY_UP_ARROW 125
# define KEY_DOWN_ARROW 126
# define KEY_LEFT_ARROW 124
# define KEY_RIGHT_ARROW 123
# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78
# define KEY_ROTATE_D 2
# define KEY_ROTATE_A 0
# define KEY_ALTITUDE_W 13
# define KEY_ALTITUDE_S 1
# define KEY_PROJECTION_SPACE 49
# define KEY_COLOR_C 8

typedef struct s_points
{
	float		x;
	float		x1;
	float		y;
	float		y1;
}				t_points;

typedef struct s_mlx
{
	void		*init;
	void		*win;
	void		*image;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct s_all
{
	t_mlx			mlx;
	int				**mapa;
	int				filas;
	int				columnas;
	int				shift_x;
	int				shift_y;
	int				zoom;
	float			altitude;
	int				color;
	unsigned int	**hex_color;
	int				x_cord;
	int				y_cord;
	int				projection;
	int				mouse_flag;
	float			axis_z_rotation;
}				t_all;

void	*ft_free_matrix(char **matrix);

float	max_nb(float a, float b);
float	normalize(float n);
char	**ft_split(char *s, char c);
char	*special_strjoin(char *s1, char *s2);
int		ft_atoi(char *str);

void	put_pixel(t_all *all, int x, int y, int color);
void	new_wind(t_all *all);
int		rgb_progressive(int i, int initial_c, int final_c, int n);
void	draw(t_all *all);
void	algorithm(t_points points, unsigned int color, t_all *all);
void	read_map(int fd, t_all *all);

int				choose_color(float z, float z1, unsigned int *color, t_all *all);
unsigned int	get_color(int i, int n, t_all *all);
unsigned int	hexadecimal(char *map, t_all *all);

int		exit_fdf(char *error, t_all *all);
int		key_press(int keycode, t_all *all);
int		key_release(int keycode, t_all *all);
int		mouse_press(int button, int x, int y, t_all *param);
int		mouse_move(int x, int y, t_all *all);
int		mouse_release(int button, int x, int y, t_all *all);

#endif
