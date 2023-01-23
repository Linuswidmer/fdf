#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void print_edges(t_edges *edges)
{
  printf("TOP_LEFT: [%f], [%f]\n", edges->top_left.x, edges->top_left.y);
  printf("TOP_ROGHT: [%f], [%f]\n", edges->top_right.x, edges->top_right.y);
  printf("BOTTOM_LEFT: [%f], [%f]\n", edges->bottom_left.x, edges->bottom_left.y);
  printf("BOTTOM_RIGHT: [%f], [%f]\n", edges->bottom_right.x, edges->bottom_right.y);
}

t_edges *map_coordinates(t_point **map, int num_lines, int line_len)
{
  float smallest_x;
  float smallest_y;
  float biggest_x;
  float biggest_y;
  int i;
  int j;
  t_edges *edges;

  smallest_x = map[i][j].x;
  smallest_y = map[i][j].y;
  biggest_x = map[i][j].x;
  biggest_y = map[i][j].y;
  i = 0;
  j = 0;
  while (i < num_lines)
  {
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
    j = 0;
    i++;

  }
  // printf("SMALLEST X %f\n", smallest_x);
  // printf("SMALLEST Y %f\n", smallest_y);
  // printf("BIGGEST X %f\n", biggest_x);
  // printf("BIGGEST Y %f\n", biggest_y);
  edges = malloc(sizeof(t_edges));
  edges->top_left.x = smallest_x;
  edges->top_left.y = smallest_y;
  edges->top_right.x = biggest_x;
  edges->top_right.y = smallest_y;
  edges->bottom_left.x = smallest_x;
  edges->bottom_left.y = biggest_y;
  edges->bottom_right.x = biggest_x;
  edges->bottom_right.y = biggest_y;
  return (edges);
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

void print_edges_to_img(t_data *img, t_edges *edges)
{
  my_mlx_pixel_put(img, (int)edges->top_left.x, (int)edges->top_left.y, 0x00FF0000);
  my_mlx_pixel_put(img, (int)edges->top_right.x, (int)edges->top_right.y, 0x00FF0000);
  my_mlx_pixel_put(img, (int)edges->bottom_left.x, (int)edges->bottom_left.y, 0x00FF0000);
  my_mlx_pixel_put(img, (int)edges->bottom_right.x, (int)edges->bottom_right.y, 0x00FF0000);
}

void window_size(t_point **map, t_data *img, int num_lines, int line_len)
{
  t_edges *edges;
  
  edges = map_coordinates(map, num_lines, line_len);
  print_edges(edges);
  img->x_len = (int)(edges->top_right.x - edges->top_left.x);
  img->y_len = (int)(edges->bottom_right.y - edges->top_right.y);

  printf("XLEN: %i\n", img->x_len);
  printf("YLEN: %i\n", img->y_len);
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

  printf("SCALE %i\n", img->scale);
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
	void	*mlx;
	void	*mlx_win;
  t_data img;
  
  mlx = mlx_init();
  window_size(map, &img, num_lines - 1, line_len);
  scale_map(map, num_lines - 1, line_len, &img);
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "./fdf");
  img.img = mlx_new_image(mlx, img.x_len * img.scale + 1, img.y_len *img.scale + 1);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  print_grid(&img, map, num_lines - 1, line_len);
  mlx_put_image_to_window(mlx, mlx_win, img.img, (WINDOW_WIDTH - img.x_len *img.scale)/2 , (WINDOW_HEIGHT - img.y_len *img.scale)/2);
  // printf("IMAGE COORDINATES: %i %i\n", (WINDOW_WIDTH - img.x_len)/2, (WINDOW_HEIGHT - img.y_len)/2);
  printf("TEST WINDOW\n");

  free_map_struct(map);
	mlx_loop(mlx);

}


int main()
{
  int fd;
  t_point **map;
  int num_lines;
  int line_len;

  // 1. Parse the map
  fd = open("./test_maps/42.fdf", O_RDONLY);
  map = parse_map(fd, &num_lines, &line_len);
  printf("NUMBER OF LINES: %i\n", num_lines - 1);
  printf("LINE LENGTH: %i \n", line_len);

  // 2. Convert map to isometric projection
  
  //3. Create window and print map to window
  window(map, num_lines, line_len);
  
  // print_edges_to_img(&img, edges);
}
