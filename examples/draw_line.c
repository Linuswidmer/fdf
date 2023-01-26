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
  // printf("W is %i\nH is %i\n", w, h);
  // printf("X is: %i\nX1 is %i\ndx1 is %i\ndx2 is %i\n", x, dx1, dx2);
  // printf("Y is: %i\nY1 is %i\ndy1 is %i\ndy2 is %i\n", y, dy1, dy2);
  // printf("Longest is %i\nShortest %i\n", longest, shortest);
  // printf("NUMERATOR IS %i\n", numerator);
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

int main()
{
	void	*mlx;
  void  *mlx_win;
  t_data  img;
  t_point p1;
  t_point p2;

  p1.x = 10;
  p1.y = 10;
  p2.x = 100;
  p2.y = 20;

	mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 720, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 420, 420);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  // my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
  
  // line(&img, p1.x, p1.y, p2.x, p2.y);
  draw_line(&img, 10, 10, 100, 100);
  draw_line(&img, 250, 100, 150, 10);
  draw_line(&img, 10, 320, 100, 10);
  draw_line(&img, 300, 120, 100, 10);
  draw_line(&img, 400, 400, 400, 400);
  // line(&img, 10, 10, 100, 100);
  printf("TTT\n");
  mlx_put_image_to_window(mlx, mlx_win, img.img, 1, 1);
  mlx_loop(mlx);

}
