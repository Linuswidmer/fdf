#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_vars{
  void *mlx;
  void *win;
} t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point {
  float x;
  float y;
}       t_point;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  // printf("DST = %s\n", dst);
	*(unsigned int*)dst = color;
  // printf("DST = %s\n", dst);
}

int close(int keycode, t_vars *vars)
{
  void **ptr;

  ptr = &vars->mlx;
  printf("%i\n", keycode);
  if (keycode == 65307)
  {
    // printf("%p\n", vars->mlx);
    mlx_loop_end(vars->mlx);
  // mlx_destroy_window(vars->mlx, vars->win);
  // mlx_destroy_display(vars->mlx);
    exit(1);
    // printf("%p\n", vars->mlx);
    //
    // ptr = NULL;
  }
  return (0);
}

int cross(t_vars *vars)
{
    mlx_loop_end(vars->mlx);

  return (0);
}

int	main(void)
{
  t_vars vars;
  t_data img;
  // int ptr;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 400, 400, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 120, 120);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
  // mlx_destroy_image(vars.mlx, &img);
  mlx_put_image_to_window(vars.mlx, vars.win, img.img, 10, 10);
  mlx_hook(vars.win, 2, 1L<<0, close, &vars);
  mlx_hook(vars.win, 17, 1L<<2, cross, &vars);
	mlx_loop(vars.mlx);
  // mlx_destroy_image(vars.mlx, &img);
  mlx_destroy_window(vars.mlx, vars.win);
  mlx_destroy_display(vars.mlx);
  printf("exited the loop\n");
  // ptr = malloc(2);
}
