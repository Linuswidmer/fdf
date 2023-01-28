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
