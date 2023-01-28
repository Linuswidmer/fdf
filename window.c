#include "fdf.h"

void rotate(t_vars *vars)
{
  (void)vars;
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
}

t_data_img blank_img(t_vars *vars)
{
  t_data_img blank;

  blank.img = mlx_new_image(vars->mlx, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1); 
  blank.addr = mlx_get_data_addr(blank.img, &blank.bits_per_pixel, &blank.line_length, &blank.endian);
  mlx_put_image_to_window(vars->mlx, vars->win, blank.img, 0, 0);
  return (blank);
}

void zoom(t_vars *vars, float zoom)
{
  t_data_img blank;
  t_data_img img_new;

  blank = blank_img(vars);
  // test here that image height and width multiplied dont exceed max int
  
  vars->img_width = vars->img_width * zoom;
  vars->img_height = vars->img_height * zoom;
  img_new.scale = vars->img.scale * zoom;
  img_new.img = mlx_new_image(vars->mlx, vars->img_width, vars->img_height);
  img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
  
  // print_map_struct(vars->map, vars->num_lines, vars->line_len);
  scale_map(vars->map, vars->num_lines, vars->line_len, zoom);
  map_size(vars->map, &img_new, vars->num_lines, vars->line_len);
  printf("SCALAR %f\n", vars->img.scale);
  printf("IMG DIMENSIONS: %f, %f\n", vars->img_width, vars->img_height);
  printf("IMG XLEN: %f\n", vars->img.x_len);
  printf("IMG YLEN: %f\n", vars->img.y_len);

  print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
  mlx_destroy_image(vars->mlx, vars->img.img);
  mlx_destroy_image(vars->mlx, blank.img);
  mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img_width)/2 , (WINDOW_HEIGHT - vars->img_height)/2);
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
  img.img = mlx_new_image(vars->mlx, vars->img_width, vars->img_height);
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
  return (vars);
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  
  vars = mlx_creator(map, num_lines, line_len);
  rotation_z(map, num_lines, line_len, 3.14 + 0.785);
  rotation_x(map, num_lines, line_len, 3.14 + 0.955);
  // rotation_y(map, num_lines, line_len, 3.14);
  // print_map_struct(map, num_lines, line_len);
  vars.img = img_creator(&vars);
  printf("MLX ADDRESS WINDOW %p\n", vars.mlx);
  
  printf("SCALAR %f\n", vars.img.scale);
  printf("IMG DIMENSIONS: %f, %f\n", vars.img_width, vars.img_height);
  
  print_map(&(vars.img), map, num_lines , line_len);
  mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, (WINDOW_WIDTH - vars.img_width)/2 , (WINDOW_HEIGHT - vars.img_height)/2);
 
  // hooks should happen late, because all info need to be stored in vars
  mlx_hook(vars.win, 2, 1L<<0, keypress_events, &vars);
  mlx_hook(vars.win, 17, 1L<<2, close_cross, &vars);
	mlx_loop(vars.mlx);

  mlx_destroy_image(vars.mlx, vars.img.img);
  mlx_destroy_window(vars.mlx, vars.win);
  free(vars.mlx);
}
