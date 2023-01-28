#include "fdf.h"

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
