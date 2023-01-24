#include <mlx.h>
#include <stdio.h>


typedef struct s_vars{
  void *mlx;
  void *win;
} t_vars;

int close(int keycode, t_vars *vars)
{
  void **ptr;

  ptr = &vars->mlx;
  printf("%i\n", keycode);
  if (keycode == 65307)
  {
    // printf("%p\n", vars->mlx);
    mlx_destroy_window(vars->mlx, vars->win);
    mlx_loop_end(vars->mlx);
    // printf("%p\n", vars->mlx);
    // ptr = NULL;
    vars->win = NULL;
  }
  return (0);
}

int	main(void)
{
  t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 400, 400, "Hello world!");
    printf("%p\n", vars.mlx);
  mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
  printf("exited the loop\n");
}
