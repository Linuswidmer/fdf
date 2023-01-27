#include "fdf.h"

void rotate(t_vars *vars)
{
  // t_data_img img_new;
  // 
  // img_new.img = mlx_new_image(vars->mlx, vars->img->x_len * vars->img->scale + 1, vars->img->y_len *vars->img->scale + 1);
  // img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
  // my_mlx_pixel_put(&img_new, 5, 5, 0x00FF0000);
  // rotation_z(vars->map, vars->num_lines, vars->line_len);
  // map_size(vars->map, &img_new, vars->num_lines , vars->line_len);
  // center_map(vars->map, vars->num_lines, vars->line_len, vars->img);
  // print_map_struct(vars->map, vars->num_lines, vars->line_len);
  // print_map(vars->img, vars->map, vars->num_lines , vars->line_len);
  // mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img->x_len * vars->img->scale)/2 , (WINDOW_HEIGHT - vars->img->y_len * vars->img->scale)/2);
  // mlx_destroy_image(vars->mlx, vars->img);
}

void zoom(t_vars *vars)
{
  t_data_img img_new;
  t_data_img blank;

  blank.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT); 
  blank.addr = mlx_get_data_addr(blank.img, &blank.bits_per_pixel, &blank.line_length, &blank.endian);
  mlx_put_image_to_window(vars->mlx, vars->win, blank.img, 0, 0);
  
  img_new.img = mlx_new_image(vars->mlx, vars->img_xlen * 0.5, vars->img_ylen * 0.5);
  img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
  // print_map_struct(vars->map, vars->num_lines, vars->line_len);
  scale_map(vars->map, vars->num_lines, vars->line_len, 0.5);
  map_size(vars->map, &img_new, vars->num_lines, vars->line_len);
  vars->img_xlen = vars->img_xlen * 0.5 + 1;
  vars->img_ylen = vars->img_ylen * 0.5 + 1;
  printf("SCALAR %f\n", vars->img.scale);
  printf("IMG DIMENSIONS: %f, %f\n", vars->img_xlen, vars->img_ylen);
  print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
  mlx_destroy_image(vars->mlx, vars->img.img);
  mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img_xlen)/2 , (WINDOW_HEIGHT - vars->img_ylen)/2);
  vars->img = img_new;
}

void map_first_setup(t_point **map, t_data_img *img, int num_lines, int line_len)
{
  float scale;

  rotation_z(map, num_lines, line_len);
  rotation_x(map, num_lines, line_len);
  
  map_size(map, img, num_lines , line_len);
  
  center_map(map, num_lines, line_len, img);
  // print_map_struct(map, num_lines, line_len);
  
  scale = compute_map_scale(img);
  img->scale = scale;
  scale_map(map, num_lines, line_len, scale);
}

void add_hooks(t_vars *vars)
{
  mlx_hook(vars->win, 2, 1L<<0, keypress_events, vars);
  mlx_hook(vars->win, 17, 1L<<2, close_cross, vars);
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  t_data_img img;
  
  vars.mlx = mlx_init();
  vars.map = map;
  vars.num_lines = num_lines;
  vars.line_len = line_len;

  map_first_setup(map, &img, num_lines, line_len);
  // print_map_struct(map, num_lines, line_len);
	
  vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "./fdf");

  printf("SCALAR %f\n", img.scale);

  vars.img_xlen = img.x_len * img.scale + 1;
  vars.img_ylen = img.y_len * img.scale + 1;
  printf("IMG DIMENSIONS: %f, %f\n", vars.img_xlen, vars.img_ylen);
  img.img = mlx_new_image(vars.mlx, vars.img_xlen, vars.img_ylen);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  vars.img = img;
  // i need to check if i can even draw
  print_map(&img, map, num_lines , line_len);
  mlx_put_image_to_window(vars.mlx, vars.win, img.img, (WINDOW_WIDTH - vars.img_xlen)/2 , (WINDOW_HEIGHT - vars.img_ylen)/2);
  // printf("IMAGE COORDINATES: %i %i\n", (WINDOW_WIDTH - img.x_len)/2, (WINDOW_HEIGHT - img.y_len)/2);
  // printf("TEST WINDOW\n");

  add_hooks(&vars);

	mlx_loop(vars.mlx);

  mlx_destroy_image(vars.mlx, img.img);
  mlx_destroy_window(vars.mlx, vars.win);
  free(vars.mlx);
}
