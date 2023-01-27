#include "fdf.h"


int close_esc(int keycode, t_vars *vars)
{
  void **ptr;

  ptr = &vars->mlx;
  // printf("%i\n", keycode);
  if (keycode == 65307)
  {
    mlx_loop_end(vars->mlx);
  }
  return (0);
}

int close_cross(t_vars *vars)
{
  mlx_loop_end(vars->mlx);
  return (0);
}

int keypress_events(int keycode, t_vars *vars)
{

  if (keycode == 65307)
  {
    mlx_loop_end(vars->mlx);
  }
  printf("%i\n", keycode);
  // a
  if (keycode == 97)
    // mlx_loop_end(vars->mlx);
  // d
  if (keycode == 100)
    rotate(vars);
  // zoom (z)
  if (keycode == 122)
    zoom(vars);
    // img_update(vars);
  return (0);
}
