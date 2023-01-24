#include "fdf.h"


void map_size(t_point **map, t_data *img, int num_lines, int line_len)
{
  float smallest_x;
  float smallest_y;
  float biggest_x;
  float biggest_y;
  int i;
  int j;

  i = 0;
  smallest_x = 0;
  smallest_y = 0;
  biggest_x = 0;
  biggest_y = 0;
  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      if (map[i][j].x < smallest_x)
            smallest_x = map[i][j].x;
      if (map[i][j].y < smallest_y)
            smallest_y = map[i][j].y;
      if (map[i][j].x > biggest_x)
            biggest_x = map[i][j].x;
      if (map[i][j].y > biggest_y)
            biggest_y = map[i][j].y;
      j++;
    }
    i++;
  }
  img->x_len = (int)(biggest_x - smallest_x);
  img->y_len = (int)(biggest_y - smallest_y);
}

void print_grid(t_data *img, t_point **map, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      my_mlx_pixel_put(img, (int)map[i][j].x, (int)map[i][j].y, 0xFFFFFFFF);
      j++;
    }
    i++;
  }
}

void scale_map(t_point **map, int num_lines, int line_len, t_data *img)
{
  int scale_x;
  int scale_y;
  int i;
  int j;

  scale_x = (WINDOW_WIDTH - 100)/img->x_len;
  scale_y = (WINDOW_HEIGHT - 100)/img->y_len;

  if (scale_x < scale_y)
      img->scale = scale_x;
  else
      img->scale = scale_y;
  i = 0;
  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      map[i][j].x = map[i][j].x * img->scale;
      map[i][j].y = map[i][j].y * img->scale;
      j++;
    }
    i++;
  }
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  t_data img;
  
  vars.mlx = mlx_init();
  map_size(map, &img, num_lines , line_len);
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "./fdf");
  
  scale_map(map, num_lines, line_len, &img);
  
  img.img = mlx_new_image(vars.mlx, img.x_len * img.scale + 1, img.y_len *img.scale + 1);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  print_grid(&img, map, num_lines , line_len);
  mlx_put_image_to_window(vars.mlx, vars.win, img.img, (WINDOW_WIDTH - img.x_len *img.scale)/2 , (WINDOW_HEIGHT - img.y_len *img.scale)/2);
  // printf("IMAGE COORDINATES: %i %i\n", (WINDOW_WIDTH - img.x_len)/2, (WINDOW_HEIGHT - img.y_len)/2);
  // printf("TEST WINDOW\n");
  
  mlx_hook(vars.win, 2, 1L<<0, close_esc, &vars);
  mlx_hook(vars.win, 17, 1L<<2, close_cross, &vars);

	mlx_loop(vars.mlx);

  mlx_destroy_image(vars.mlx, img.img);
  mlx_destroy_window(vars.mlx, vars.win);
  free(vars.mlx);
}
