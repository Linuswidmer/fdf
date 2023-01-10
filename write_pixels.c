#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>


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

void print_raute(t_data img)
{
  int i;
  int j;

  i = 200;
  j = 200;
  while (i > 100)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    i--;
    j--;
  }
  while (j > 0)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    j--;
    i++;
  }
  while (i < 199)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    i++;
    j++;
  }
  while (j < 199)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    j++;
    i--;
  }
}


void print_square(t_data img)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (i < 100)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    i++;
  }
  while (j < 100)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    j++;
  }
  while (i > 0)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    i--;
  }
  while (j > 0)
  {
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    j--;
  }
}

int my_round(float num)
{
  return (num /1);
}

void connect_points(t_data img, t_point *p1, t_point *p2)
{
  float dif_x;
  float dif_y;
  float start_x;
  float start_y;
  float end_x;
  float end_y;
  float ratio;
  float i;
  float j;
  float slope;

  slope = 0;
  start_x = p1->x;
  start_y = p1->y;
  end_x = p2->x;
  end_y = p2->y;

  my_mlx_pixel_put(&img, start_x, start_y, 0x00FF0000);
  my_mlx_pixel_put(&img, end_x, end_y, 0x00FF0000);
  i = 0;
  j = 0;
  dif_x = end_x - start_x;
  dif_y = end_y - start_y;
  printf("%f\n", dif_x);
  printf("%f\n", dif_y);
  ratio = dif_x / dif_y;
  printf("%f\n", ratio);
  while(start_y + j < end_y)
  {
    i = i + ratio;
    my_mlx_pixel_put(&img, start_x + my_round(i), start_y + j, 0x00FF0000);
    j++;
  }

}

int	main(void)
{
	void	*mlx;
  void  *mlx_win;
  t_data img;
  t_data img2;
  t_point *p1;
  t_point *p2;
  
  p1 = malloc(sizeof(t_point));
  p2 = malloc(sizeof(t_point));
  p1->x = 5;
  p1->y = 5;
  p2->x = 205;
  p2->y = 55;

	mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 720, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 420, 420);
	// img2.img = mlx_new_image(mlx, 420, 420);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  // img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
 //  printf("LENGTH is%i\n", img.line_length);
 //  printf("Bit per pixel%i\n", img.bits_per_pixel);
	// printf("ADDRESS is%s\n", img.addr);
  // one line is for byte, therefore the linelength is the width of the image multiplied by 
  // bits per pixel and then divided by 8
    // my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
  // print_square(img);
  // print_raute(img2);
  connect_points(img, p1, p2);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 1, 1);
  // mlx_put_image_to_window(mlx, mlx_win, img2.img, 320,140);
  mlx_loop(mlx);
}

