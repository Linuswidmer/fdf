/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:46:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/30 11:56:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 782

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
void		map_int_to_struct(t_point **map_struct, int **map_int, int num_lines, int line_len);
int			*line_to_int(char **line, int *line_len);

void		print_map_int(int **map, int num_lines, int line_len);
void		free_map_struct(t_point **map, int num_lines);
void		free_map_int(int **map, int num_lines);
void		free_line(char **line_split, char *line);

void		map_size(t_vars *vars, t_point **map, t_data_img *img);
void		calc_map_params(t_vars *vars, t_data_img *img);
void		scale_map(t_point **map, int num_lines, int line_len, float scale);
void		translate_map(t_vars *vars, float trans_x, float trans_y);

void		window(t_point **map, int num_lines, int line_len);
t_vars		mlx_creator(t_point **map, int num_lines, int line_len);
t_data_img	img_creator(t_vars *vars);

int			keypress_events(int keycode, t_vars *vars);
int			close_cross(t_vars *vars);
void		rotate(t_vars *vars);
int			zoom(t_vars *vars, float zoom);

void		my_mlx_pixel_put(t_data_img *data, int x, int y, int color);
void		draw_line(t_data_img *img, int x, int y, int x2, int y2);
void		print_map(t_data_img *img, t_point **map, int num_lines, int line_len);
void		rotation_x(t_point **map, int num_lines, int line_len, double rad);
void		rotation_y(t_point **map, int num_lines, int line_len, double rad);
void		rotation_z(t_point **map, int num_lines, int line_len, double rad);

#endif
