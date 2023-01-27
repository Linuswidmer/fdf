#include "fdf.h"

// void rotate(t_vars *vars)
// {
//   t_data_img img_new;
//   t_data_img blank;
//
//   blank.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT); 
//   blank.addr = mlx_get_data_addr(blank.img, &blank.bits_per_pixel, &blank.line_length, &blank.endian);
//   mlx_put_image_to_window(vars->mlx, vars->win, blank.img, 0, 0);
//   
//   img_new.img = mlx_new_image(vars->mlx, vars->img_xlen, vars->img_ylen);
//   img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
//   
//   // print_map_struct(vars->map, vars->num_lines, vars->line_len);
//   rotation_z(vars->map, vars->num_lines, vars->line_len, 0.785);
//   map_size(vars->map, &img_new, vars->num_lines, vars->line_len);
//   vars->img_xlen = vars->img_xlen + 1;
//   vars->img_ylen = vars->img_ylen + 1;
//   img_new.scale = vars->img.scale;
//   printf("SCALAR %f\n", vars->img.scale);
//   printf("IMG DIMENSIONS: %f, %f\n", vars->img_xlen, vars->img_ylen);
//   
//   print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
//   mlx_destroy_image(vars->mlx, vars->img.img);
//   mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img_xlen)/2 , (WINDOW_HEIGHT - vars->img_ylen)/2);
//   vars->img = img_new;
//
// }

void zoom(t_vars *vars, float zoom)
{
  t_data_img img_new;
  t_data_img blank;

  blank.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT); 
  blank.addr = mlx_get_data_addr(blank.img, &blank.bits_per_pixel, &blank.line_length, &blank.endian);
  mlx_put_image_to_window(vars->mlx, vars->win, blank.img, 0, 0);

  // max image size has to be 100 px smaller
  
  img_new.img = mlx_new_image(vars->mlx, vars->img_xlen * zoom, vars->img_ylen * zoom);
  img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
  
  // print_map_struct(vars->map, vars->num_lines, vars->line_len);
  scale_map(vars->map, vars->num_lines, vars->line_len, zoom);
  map_size(vars->map, &img_new, vars->num_lines, vars->line_len);
  vars->img_xlen = vars->img_xlen * zoom + 1;
  vars->img_ylen = vars->img_ylen * zoom + 1;
  img_new.scale = vars->img.scale * zoom;
  printf("SCALAR %f\n", vars->img.scale);
  printf("IMG DIMENSIONS: %f, %f\n", vars->img_xlen, vars->img_ylen);
  
  print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
  mlx_destroy_image(vars->mlx, vars->img.img);
  mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img_xlen)/2 , (WINDOW_HEIGHT - vars->img_ylen)/2);
  vars->img = img_new;
}

t_data_img img_creator(t_vars *vars)
{
  t_data_img img;

  map_size(vars->map, &img, vars->num_lines, vars->line_len);
  center_map(vars->map, vars->num_lines, vars->line_len, &img);
  vars->img = img; 
  img.scale = compute_map_scale(vars);
  scale_map(vars->map, vars->num_lines, vars->line_len, img.scale);
  img.img = mlx_new_image(vars->mlx, vars->img_xlen, vars->img_ylen);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  vars->img = img; 
  return (img);
}

t_vars mlx_creator(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  
  vars.mlx = mlx_init();
  vars.map = map;
  vars.num_lines = num_lines;
  vars.line_len = line_len;
  vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "./fdf");
  mlx_hook(vars.win, 2, 1L<<0, keypress_events, &vars);
  mlx_hook(vars.win, 17, 1L<<2, close_cross, &vars);
  return (vars);
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  t_data_img img;
  
  vars = mlx_creator(map, num_lines, line_len);
  rotation_z(map, num_lines, line_len, 3.14 + 0.785);
  rotation_x(map, num_lines, line_len, 3.14 + 0.955);
  // rotation_y(map, num_lines, line_len, 3.14);
  // print_map_struct(map, num_lines, line_len);
  img = img_creator(&vars);
  
  printf("SCALAR %f\n", img.scale);
  printf("IMG DIMENSIONS: %f, %f\n", vars.img_xlen, vars.img_ylen);
  
  print_map(&img, map, num_lines , line_len);
  mlx_put_image_to_window(vars.mlx, vars.win, img.img, (WINDOW_WIDTH - vars.img_xlen)/2 , (WINDOW_HEIGHT - vars.img_ylen)/2);

	mlx_loop(vars.mlx);

  mlx_destroy_image(vars.mlx, img.img);
  mlx_destroy_window(vars.mlx, vars.win);
  free(vars.mlx);
}
