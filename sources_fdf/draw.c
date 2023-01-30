#include "fdf.h"

int abs(int x)
{
  if (x < 0)
    return (-x);
  else
    return (x);
}

void	my_mlx_pixel_put(t_data_img *img, int x, int y, int color)
{
	char	*dst;

  if (x > 0 &&  x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
  {
	  dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	  *(unsigned int*)dst = color;
  }
}

void line_to_img(t_data_img *img, t_data_line* line)
{
  int i;

  i = 0;
  while (i <= line->longest)
  {
    my_mlx_pixel_put(img, line->x, line->y, 0xFFFFFFFF);
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
  line->dx1 = 0;
  line->dx2 = 0;
  line->dy1 = 0;
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

void draw_line(t_data_img *img, int x, int y, int x2, int y2)
{
  t_data_line line;

    line.x = x;
    line.y = y;
    line.x2 = x2;
    line.y2 = y2;
    calc_line_params(&line);
    line_to_img(img, &line);
}

void print_map(t_data_img *img, t_point **map, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  while (i < num_lines)
  {
    j = 0;
    while (j < line_len)
    {
      if (i < num_lines - 1)
        draw_line(img, (int)map[i][j].x, (int)map[i][j].y, (int)map[i + 1][j].x, (int)map[i + 1][j].y);
      if (j < line_len - 1)
        draw_line(img, (int)map[i][j].x, (int)map[i][j].y, (int)map[i ][j +1].x, (int)map[i][j + 1].y);
      j++;
    }
    i++;
  }
}

