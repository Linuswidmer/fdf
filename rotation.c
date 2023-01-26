#include "fdf.h"

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
      map[i][j].y = 0 + (float)(y * cos(0.955) - z * sin(0.955));
      map[i][j].z = (float)(0 + y * sin(0.955) + z * cos(0.955));
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
      map[i][j].x = (float)(x * cos(0.785) - y * sin(0.785) + 0);
      map[i][j].y = (float)(x * sin(0.785) + y * cos(0.785) + 0);
      // map[i][j].z = (float)(x * sin(0.78) + z * cos(0.78));
      j++;
    }
    i++;
  }
}
