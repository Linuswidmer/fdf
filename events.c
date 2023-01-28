#include "fdf.h"

int close_cross(t_vars *vars)
{
  mlx_loop_end(vars->mlx);
  return (0);
}

void blank_img(t_vars *vars)
{
  t_data_img blank;

  blank.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT); 
  blank.addr = mlx_get_data_addr(blank.img, &blank.bits_per_pixel, &blank.line_length, &blank.endian);
  mlx_put_image_to_window(vars->mlx, vars->win, blank.img, 0, 0);
  mlx_destroy_image(vars->mlx, blank.img);
}

int zoom(t_vars *vars, float zoom)
{
  t_data_img img_new;

  if (vars->img_width * zoom < 15000 && vars->img_height * zoom < 15000)
  {
    if (vars->img_width * zoom < vars->line_len && vars->img_height * zoom < vars->num_lines)
    {
      return (0);
    }
    blank_img(vars);
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
    mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img_width)/2 , (WINDOW_HEIGHT - vars->img_height)/2);
    vars->img = img_new;
  }
  return (0);
}

void rotate(t_vars *vars)
{
  (void)vars;
}

void translate_map_y(t_vars *vars, int trans)
{
  int i;
  int j;

  i = 0;
  while (i < vars->num_lines)
  {
    j = 0;
    while (j < vars->line_len)
    {
        // map[i][j].x =  map[i][j].x + trans;
        (vars->map)[i][j].y = (vars->map)[i][j].y + trans; 
      j++;
    }
    i++;
  }
}

void translate_y(t_vars *vars, int trans)
{
  t_data_img img_new;
  blank_img(vars);
  
  img_new.img = mlx_new_image(vars->mlx, vars->img_width, vars->img_height);
  img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
  img_new.scale = 1;
  translate_map_y(vars, trans);
  map_size(vars->map, &img_new, vars->num_lines, vars->line_len);
  print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
  mlx_destroy_image(vars->mlx, vars->img.img);
  mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, (WINDOW_WIDTH - vars->img_width)/2 , (WINDOW_HEIGHT - vars->img_height)/2);
  vars->img = img_new;
  printf("trans %i\n", trans);
}


int keypress_events(int keycode, t_vars *vars)
{

  printf("%i\n", keycode);
  if (keycode == 122) //z
    zoom(vars, 0.5);
  else if (keycode == 120) //x
    zoom(vars, 2);
  else if (keycode == 65307) //esc
    mlx_loop_end(vars->mlx);
  else if (keycode == 119) //w
    translate_y(vars, 2);
  else if (keycode == 115) //s
    translate_y(vars, -2);
  return (0);
}
