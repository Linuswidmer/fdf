#ifndef FDF_H
#define FDF_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "mlx.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 782

typedef struct s_vars{
  void *mlx;
  void *win;
} t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
  int x_len;
  int y_len;
  int scale;
}				t_data;

typedef struct s_point {
  float x;
  float y;
  float z;
} t_point;

t_point **parse_map(int fd, int *num_lines, int *line_len);
int **map_to_int(int fd, int **map, int *num_lines, int *line_len);
t_point **map_struct_creator(int num_lines, int line_len);
void map_int_to_struct(t_point **map_struct, int **map_int, int num_lines, int line_len);

void print_map_int(int **map, int num_lines, int line_len);
void print_map_struct(t_point **map, int num_lines, int line_len);
void free_map_struct(t_point **map, int num_lines);
void  free_map_int(int **map, int num_lines);
void free_line(char **line_split, char *line);

void map_size(t_point **map, t_data *img, int num_lines, int line_len);
void print_grid(t_data *img, t_point **map, int num_lines, int line_len);
void scale_map(t_point **map, int num_lines, int line_len, t_data *img);
void window(t_point **map, int num_lines, int line_len);

int close_esc(int keycode, t_vars *vars);
int close_cross(t_vars *vars);

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif
