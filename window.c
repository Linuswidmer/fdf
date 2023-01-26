#include "fdf.h"

int keypress_events(int keycode, t_vars *vars)
{
  t_data_img img_new;

  if (keycode == 65307)
  {
    mlx_loop_end(vars->mlx);
  }
  printf("%i\n", keycode);
  // a
  if (keycode == 97)
  {
    // mlx_loop_end(vars->mlx);
  }
  // d
  if (keycode == 100)
  {
  img_new.img = mlx_new_image(vars->mlx, vars->img->x_len * vars->img->scale + 1, vars->img->y_len *vars->img->scale + 1);
  img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
  // my_mlx_pixel_put(&img_new, 5, 5, 0x00FF0000);
  rotation_z(vars->map, vars->num_lines, vars->line_len);
  // map_size(vars->map, &img_new, vars->num_lines , vars->line_len);
  // center_map(vars->map, vars->num_lines, vars->line_len, vars->img);
  print_map_struct(vars->map, vars->num_lines, vars->line_len);
  print_map(vars->img, vars->map, vars->num_lines , vars->line_len);
  mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img->x_len * vars->img->scale)/2 , (WINDOW_HEIGHT - vars->img->y_len * vars->img->scale)/2);
  // mlx_destroy_image(vars->mlx, vars->img);
  }
  return (0);
}

void transform_map(t_point **map, t_data_img *img, int num_lines, int line_len)
{
  rotation_z(map, num_lines, line_len);
  rotation_x(map, num_lines, line_len);
  // rotation_y(map, num_lines, line_len);
  
  map_size(map, img, num_lines , line_len);
  
  center_map(map, num_lines, line_len, img);
  // print_map_struct(map, num_lines, line_len);
  scale_map(map, num_lines, line_len, img);
}

void add_hooks(t_vars *vars)
{
  // mlx_hook(vars->win, 2, 1L<<0, close_esc, vars);
  mlx_hook(vars->win, 2, 1L<<0, keypress_events, vars);
  mlx_hook(vars->win, 17, 1L<<2, close_cross, vars);
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  t_data_img img;
  
  vars.mlx = mlx_init();
  vars.img = &img;
  vars.map = map;
  vars.num_lines = num_lines;
  vars.line_len = line_len;

  transform_map(map, &img, num_lines, line_len);
  // print_map_struct(map, num_lines, line_len);
	
  vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "./fdf");

  printf("SCALARS %i\n", img.scale);
  printf("IMG DIMENSIONS: %f, %f\n", img.x_len * img.scale, img.y_len * img.scale);
 
  img.img = mlx_new_image(vars.mlx, img.x_len * img.scale + 1, img.y_len *img.scale + 1);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  // i need to check if i can even draw
  print_map(&img, map, num_lines , line_len);
  mlx_put_image_to_window(vars.mlx, vars.win, img.img, (WINDOW_WIDTH - img.x_len *img.scale)/2 , (WINDOW_HEIGHT - img.y_len *img.scale)/2);
  // printf("IMAGE COORDINATES: %i %i\n", (WINDOW_WIDTH - img.x_len)/2, (WINDOW_HEIGHT - img.y_len)/2);
  // printf("TEST WINDOW\n");

  add_hooks(&vars);

	mlx_loop(vars.mlx);

  mlx_destroy_image(vars.mlx, img.img);
  mlx_destroy_window(vars.mlx, vars.win);
  free(vars.mlx);
}
