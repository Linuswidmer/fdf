#include "fdf.h"


void scale_map(t_point **map, int num_lines, int line_len, float scale)
{
  int i;
  int j;

  i = 0;
  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      map[i][j].x = map[i][j].x * scale;
      map[i][j].y = map[i][j].y * scale;
      map[i][j].z = map[i][j].z * scale;
      j++;
    }
    i++;
  }
}

void translate_map(t_vars *vars, float trans_x, float trans_y)
{
  int i;
  int j;

  i = 0;
  while (i < vars->num_lines)
  {
    j = 0;
    while (j < vars->line_len)
    {
        (vars->map)[i][j].x = (vars->map)[i][j].x + trans_x; 
        (vars->map)[i][j].y = (vars->map)[i][j].y + trans_y; 
      j++;
    }
    i++;
  }
}

void map_size(t_vars *vars, t_point **map, t_data_img *img)
{
  float biggest_x;
  float biggest_y;
  int i;
  int j;

  i = 0;
  img->smallest_x = 0;
  img->smallest_y = 0;
  biggest_x = 0;
  biggest_y = 0;
  while (i < vars->num_lines)
  {
    j = 0;
    while (j < vars->line_len)
    {
      if (map[i][j].x < img->smallest_x)
            img->smallest_x = map[i][j].x;
      if (map[i][j].y < img->smallest_y)
            img->smallest_y = map[i][j].y;
      if (map[i][j].x > biggest_x)
            biggest_x = map[i][j].x;
      if (map[i][j].y > biggest_y)
            biggest_y = map[i][j].y;
      j++;
    }
    i++;
  }
  img->x_len = biggest_x - img->smallest_x;
  img->y_len = biggest_y - img->smallest_y;
  if (img->x_len < img->y_len)
      img->scale = WINDOW_WIDTH/img->x_len;
  else
      img->scale = WINDOW_HEIGHT/img->y_len;
}
