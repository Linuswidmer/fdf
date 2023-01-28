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
  img->x_len = biggest_x - smallest_x;
  img->y_len = biggest_y - smallest_y;
  printf("SMALLLEST X %f\n", smallest_x);
  printf("SMALLLEST Y %f\n", smallest_y);
  printf("IMG X_LEN: %f\n", img->x_len);
  printf("IMG Y_LEN: %f\n", img->y_len);
  
  // scale_x = (WINDOW_WIDTH - 100)/img->x_len;
  // scale_y = (WINDOW_HEIGHT - 100)/img->y_len;
  // if (scale_x < scale_y)
  // {
  //     vars->img_xlen = vars->img.x_len * scale_x + 1;
  //     vars->img_ylen = vars->img.y_len * scale_y + 1;
  //     return (scale_x);
  // }
//   else
//   {
//       vars->img_xlen = vars->img.x_len * scale_x + 1;
//       vars->img_ylen = vars->img.y_len * scale_y + 1;
//       return (scale_y);
//   }
}

float compute_map_scale(t_vars *vars)
{
  float scale_x;
  float scale_y;
  
  scale_x = (WINDOW_WIDTH - 100)/vars->img.x_len;
  scale_y = (WINDOW_HEIGHT - 100)/vars->img.y_len;
  if (scale_x < scale_y)
  {
      vars->img_width = vars->img.x_len * scale_x + 1;
      vars->img_height = vars->img.y_len * scale_y + 1;
      return (scale_x);
  }
  else
  {
      vars->img_width = vars->img.x_len * scale_x + 1;
      vars->img_height = vars->img.y_len * scale_y + 1;
      return (scale_y);
  }
}

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

// int center_map( t_point **map, int num_lines, int line_len, t_data_img img)
// {
//   int i;
//   int j;
//
//   printf("SCALAR %f\n", img.scale);
//   printf("CENTER X AND Y: %f, %f\n", img.smallest_x, img.smallest_y);
//   // print_map_struct(map, num_lines, line_len);
//   while (i < num_lines)
//   {
//     j = 0;
//     while (j < line_len)
//     {
//       // printf("test");
//       if (img.smallest_x < 0)
//         map[i][j].x =  map[i][j].x - (img.smallest_x * img.scale);
//       if (img.smallest_y < 0)
//         map[i][j].y = map[i][j].y - (img.smallest_y * img.scale); 
//       j++;
//     }
  //   i++;
  // }
  // return (0);
 // }

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
