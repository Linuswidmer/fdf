#include "fdf.h"

int close_cross(t_vars *vars)
{
  mlx_loop_end(vars->mlx);
  return (0);
}

int zoom(t_vars *vars, float zoom)
{
  t_data_img img_new;

    img_new.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (img_new.img)
    {
      img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
      scale_map(vars->map, vars->num_lines, vars->line_len, zoom);
      print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
      mlx_destroy_image(vars->mlx, vars->img.img);
      mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, 0, 0);
      vars->img = img_new;
    }
  return (0);
}

void event_rotate(t_vars *vars, double rad_x, double rad_y, double rad_z)
{
  t_data_img img_new;
  
  img_new.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  if (img_new.img)
  {
    img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
    if(rad_x)
      rotation_x(vars->map, vars->num_lines, vars->line_len, rad_x);
    if(rad_y)
      rotation_y(vars->map, vars->num_lines, vars->line_len, rad_y);
    if(rad_z)
      rotation_z(vars->map, vars->num_lines, vars->line_len, rad_z);
    print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
    mlx_destroy_image(vars->mlx, vars->img.img);
    mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, 0,0);
    vars->img = img_new;
  }
}

void event_translate(t_vars *vars, int trans_x, int trans_y)
{
  t_data_img img_new;
  
  img_new.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  if (img_new.img)
  {
    img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, &img_new.line_length, &img_new.endian);
    if (trans_x)
      translate_map(vars, trans_x, 0);
    if (trans_y)
      translate_map(vars, 0, trans_y);
    print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
    mlx_destroy_image(vars->mlx, vars->img.img);
    mlx_put_image_to_window(vars->mlx, vars->win, img_new.img,0,0);
    vars->img = img_new;
  }
}

int keypress_events(int keycode, t_vars *vars)
{
  if (keycode == 122) //z
    zoom(vars, 0.5);
  else if (keycode == 120) //x
    zoom(vars, 2);
  else if (keycode == 65307) //esc
    mlx_loop_end(vars->mlx);
  else if (keycode == 119) //w
    event_translate(vars, 0, 10);
  else if (keycode == 115) //s
    event_translate(vars, 0, -10);
  else if(keycode == 97)
    event_translate(vars, 10, 0);
  else if(keycode == 100)
    event_translate(vars, -10, 0);
  else if(keycode == 121)
    event_rotate(vars, 0.0628, 0, 0);
  else if(keycode == 117)
    event_rotate(vars, -0.0628, 0, 0);
  else if(keycode == 104)
    event_rotate(vars, 0, 0.0628, 0);
  else if(keycode == 106)
    event_rotate(vars, 0, -0.0628, 0);
  else if(keycode == 110)
    event_rotate(vars, 0, 0, 0.0628);
  else if(keycode == 109)
    event_rotate(vars, 0, 0, -0.0628);
  return (0);
}
