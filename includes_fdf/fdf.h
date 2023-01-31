/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:46:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/31 10:20:18 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 600

typedef struct s_data_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float	x_len;
	float	y_len;
	float	scale;
	float	smallest_x;
	float	smallest_y;
	float	biggest_x;
	float	biggest_y;
}			t_data_img;

typedef struct s_point {
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_vars{
	void		*mlx;
	void		*win;
	t_data_img	img;
	t_point		**map;
	float		img_width;
	float		img_height;
	int			num_lines;
	int			line_len;
	float		rotation_x;
	float		rotation_y;
	float		rotation_z;
}				t_vars;

typedef struct s_data_line{
	int	x;
	int	y;
	int	x2;
	int	y2;
	int	w;
	int	h;
	int	dx1;
	int	dx2;
	int	dy1;
	int	dy2;
	int	longest;
	int	shortest;
	int	numerator;
}		t_data_line;

t_point		**parse_map(int fd, int *num_lines, int *line_len);
int			**map_to_int(int fd, int **map, int *num_lines, int *line_len);
t_point		**map_struct_creator(int num_lines, int line_len);
int			*line_to_int(char **line, int *line_len);
void		map_i_to_s(t_point **map_struct, int **map_int, int nl, int ll);

void		free_map_struct(t_point **map, int num_lines);
void		free_map_int(int **map, int num_lines);
int			**free_line(char **line_split, char *line, int **map, int **map_t);
float		abs_f(float x);

void		map_size(t_vars *vars, t_point **map, t_data_img *img);
void		calc_map_params(t_vars *vars, t_data_img *img);
void		scale_map(t_point **map, int num_lines, int line_len, float scale);
void		translate_map(t_vars *vars, float trans_x, float trans_y);

void		window(t_point **map, int num_lines, int line_len);
t_vars		mlx_creator(t_point **map, int num_lines, int line_len);
t_data_img	img_creator(t_vars *vars);

int			keypress_events(int keycode, t_vars *vars);
int			close_cross(t_vars *vars);
int			auto_motion(t_vars *vars);

void		my_mlx_pixel_put(t_data_img *data, int x, int y, int color);
void		print_map(t_data_img *img, t_point **map, int nl, int ll);
void		rotation_x(t_point **map, int num_lines, int line_len, double rad);
void		rotation_y(t_point **map, int num_lines, int line_len, double rad);
void		rotation_z(t_point **map, int num_lines, int line_len, double rad);

void		event_rotate(t_vars *vars, double r_x, double r_y, double r_z);

int			close_cross(t_vars *vars);
int			auto_motion(t_vars *vars);
void		two_d(t_vars *vars);

#endif
