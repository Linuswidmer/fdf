#include "fdf.h"

void rotation_x(t_point **map, int num_lines, int line_len, double rad)
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
      map[i][j].y = 0 + (float)(y * cos(rad) - z * sin(rad));
      map[i][j].z = (float)(0 + y * sin(rad) + z * cos(rad));
      j++;
    }
    i++;
  }
}

void rotation_y(t_point **map, int num_lines, int line_len, double rad)
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
      map[i][j].x = (float)(x * cos(rad) + 0 - z * sin(rad));
      map[i][j].y = map[i][j].y;
      map[i][j].z = (float)(x * sin(rad) + z * cos(rad));
      j++;
    }
    i++;
  }
}

void rotation_z(t_point **map, int num_lines, int line_len, double rad)
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
      map[i][j].x = (float)(x * cos(rad) - y * sin(rad) + 0);
      map[i][j].y = (float)(x * sin(rad) + y * cos(rad) + 0);
      // map[i][j].z = (float)(x * sin(0.78) + z * cos(0.78));
      j++;
    }
    i++;
  }
}
