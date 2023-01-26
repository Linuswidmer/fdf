#include "fdf.h"

void map_size(t_point **map, t_data_img *img, int num_lines, int line_len)
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
  img->x_len = biggest_x - smallest_x;
  img->y_len = biggest_y - smallest_y;
  img->smallest_x = smallest_x;
  img->smallest_y = smallest_y;
  printf("SMALLLEST X %f\n", smallest_x);
  printf("SMALLLEST Y %f\n", smallest_y);
  printf("IMG X_LEN: %f\n", img->x_len);
  printf("IMG Y_LEN: %f\n", img->y_len);
}

void scale_map(t_point **map, int num_lines, int line_len, t_data_img *img)
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
      map[i][j].x = map[i][j].x * (float)img->scale;
      map[i][j].y = map[i][j].y * (float)img->scale;
      j++;
    }
    i++;
  }
}

void rotation_x(t_point **map, int num_lines, int line_len)
{
  int i;
  int j;
  double x;
  double y;
  double z;

  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      x = (double)(map[i][j].x);
      y = (double)(map[i][j].y);
      z = (double)(map[i][j].z);
      map[i][j].x = map[i][j].x;
      map[i][j].y = 0 + (float)(y * cos(0.52) - z * sin(0.52));
      map[i][j].z = (float)(0 + y * sin(0.52) + z * cos(0.52));
      j++;
    }
    i++;
  }
}

void rotation_y(t_point **map, int num_lines, int line_len)
{
  int i;
  int j;
  double x;
  double y;
  double z;

  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      x = (double)(map[i][j].x);
      y = (double)(map[i][j].y);
      z = (double)(map[i][j].z);
      map[i][j].x = (float)(x * cos(5.76) + 0 - z * sin(5.76));
      map[i][j].y = map[i][j].y;
      map[i][j].z = (float)(x * sin(5.76) + z * cos(5.76));
      j++;
    }
    i++;
  }
}

void rotation_z(t_point **map, int num_lines, int line_len)
{
  int i;
  int j;
  double x;
  double y;
  double z;

  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      x = (double)(map[i][j].x);
      y = (double)(map[i][j].y);
      z = (double)(map[i][j].z);
      map[i][j].x = (float)(x * cos(0.52) - y * sin(0.52) + 0);
      map[i][j].y = (float)(x * sin(0.52) + y * cos(0.52) + 0);
      // map[i][j].z = (float)(x * sin(0.78) + z * cos(0.78));
      j++;
    }
    i++;
  }
}

int center_map(t_point **map, int num_lines, int line_len, float smallest_x, float smallest_y)
{
  int i;
  int j;

  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      if (smallest_x < 0)
        map[i][j].x =  map[i][j].x - smallest_x;
      if (smallest_y < 1)
        map[i][j].y = map[i][j].y + (smallest_y * -1); 
      j++;
    }
    i++;
  }
  return (0);
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  t_data_img img;
  
  vars.mlx = mlx_init();
  
  rotation_z(map, num_lines, line_len);
  rotation_x(map, num_lines, line_len);
  rotation_y(map, num_lines, line_len);
  
  map_size(map, &img, num_lines , line_len);
  
  center_map(map, num_lines, line_len, img.smallest_x, img.smallest_y);
  print_map_struct(map, num_lines, line_len);
  scale_map(map, num_lines, line_len, &img);
  
  // print_map_struct(map, num_lines, line_len);
  // center_map(map, num_lines, line_len, img.smallest_x, img.smallest_y);
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "./fdf");

  printf("SCALARS %i\n", img.scale);
  printf("IMG DIMENSIONS: %i, %i\n", img.x_len * img.scale, img.y_len * img.scale);
 
  img.img = mlx_new_image(vars.mlx, img.x_len * img.scale + 1, img.y_len *img.scale + 1);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  print_map(&img, map, num_lines , line_len);
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
