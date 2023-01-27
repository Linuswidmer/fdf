#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point {
  float x;
  float y;
}       t_point;

typedef struct s_data_line {
  int x;
  int y;
  int x2;
  int y2;
  int w;
  int h;
  int dx1;
  int dy1;
  int dx2;
  int dy2;
  int longest;
  int shortest;
  int numerator;
} t_data_line;

typedef struct s_vars{
  void *mlx;
  void *win;
  t_data img;
  t_point **map;
  float img_xlen;
  float img_ylen;
  int num_lines;
  int line_len;
  int x;
} t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int abs(int x)
{
  if (x < 0)
    return (-x);
  else
    return (x);
}

void line_to_img(t_data *img, t_data_line* line)
{
  int i;

  i = 0;
  while (i <= line->longest)
  {
    my_mlx_pixel_put(img, line->x, line->y, 0x00FF0000);
    line->numerator += line->shortest;
    if (!(line->numerator < line->longest))
    {
      line->numerator -= line->longest;
      line->x += line->dx1;
      line->y += line->dy1;
    }
    else
    {
      line->x += line->dx2;
      line->y += line->dy2;
    }
    i++;
  }
}

void calc_line_params(t_data_line *line)
{
  line->w = line->x2 - line->x;
  line->h = line->y2 - line->y;
  line->dy2 = 0; //has to be set
  if (line->w < 0)
  {
    line->dx1 = -1;
    line->dx2 = -1;
  }
  else if (line->w > 0)
  {
    line->dx1 = 1;
    line->dx2 = 1;
  }
  if (line->h < 0)
    line->dy1 = -1;
  else if (line->h > 0)
    line->dy1 = 1;
  line->longest = abs(line->w);
  line->shortest = abs(line->h);
  if (!(line->longest > line->shortest))
  {
    line->longest = abs(line->h);
    line->shortest = abs(line->w);
    if (line->h < 0)
      line->dy2 = -1;
    else
      line->dy2 = 1;
    line->dx2 = 0;
  }
  line->numerator = line->longest >> 1;
}

void draw_line(t_data *img, int x, int y, int x2, int y2)
{
  t_data_line line;

  line.x = x;
  line.y = y;
  line.x2 = x2;
  line.y2 = y2;
  calc_line_params(&line);
  line_to_img(img, &line);
}

void img_update(t_vars *vars)
{
  t_data img2;

  img2.img = mlx_new_image(vars->mlx, 420, 420);
  img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
  // my_mlx_pixel_put(&img2, 50, 50, 0x00FF0000);

  mlx_destroy_image(vars->mlx, vars->img.img);
  draw_line(&img2, 20, 100, 158, vars->x);

  vars->x = vars->x + 20;

  mlx_put_image_to_window(vars->mlx, vars->win, img2.img, 1, 1);
  vars->img = img2;
  printf("Test\n");
}

int keypress_events(int keycode, t_vars *vars)
{

  if (keycode == 65307)
  {
    mlx_loop_end(vars->mlx);
  }
  printf("%i\n", keycode);
  // zoom (z)
  if (keycode == 122)
  {
        img_update(vars);
  }
  return (0);
}

int main()
{
  t_vars vars;

  vars.x = 200;
	vars.mlx = mlx_init();
  vars.win = mlx_new_window(vars.mlx, 720, 720, "Hello world!");
	vars.img.img = mlx_new_image(vars.mlx, 420, 420);
  vars.img.addr = mlx_get_data_addr(vars.img.img, &(vars.img.bits_per_pixel), &(vars.img.line_length), &(vars.img.endian));
  // my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
  
  // line(&img, p1.x, p1.y, p2.x, p2.y);
  draw_line(&(vars.img), 10, 10, 100, 100);
  draw_line(&(vars.img), 250, 100, 150, 10);
  // line(&img, 10, 10, 100, 100);
  
  mlx_hook(vars.win, 2, 1L<<0, keypress_events, &vars);
  

  mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 1, 1);
  mlx_loop(vars.mlx);

}
