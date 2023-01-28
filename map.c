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

int center_map(t_point **map, int num_lines, int line_len, t_data_img *img)
{
  int i;
  int j;

  i = 0;
  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      if (img->smallest_x < 0)
        map[i][j].x =  map[i][j].x - img->smallest_x;
      if (img->smallest_y < 0)
        map[i][j].y = map[i][j].y + (img->smallest_y * -1); 
      j++;
    }
    i++;
  }
  return (0);
}
