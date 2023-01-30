#include "fdf.h"

t_point **parse_map(int fd, int *num_lines, int *line_len)
{
  int **map_int;
  t_point **map_struct;

  map_int = map_to_int(fd, 0, num_lines, line_len);
  (*num_lines)--;
  printf("LINE LENGTH %i\n", *line_len);
  printf("NUMBER OF LINE%i\n", *num_lines);
  // print_map_int(map_int, *num_lines, *line_len);
  map_struct = map_struct_creator(*num_lines, *line_len);
  map_int_to_struct(map_struct, map_int, *num_lines, *line_len);
  free_map_int(map_int, *num_lines);
  // print_map_struct(map_struct, *num_lines, *line_len);
  return (map_struct);
}

void window(t_point **map, int num_lines, int line_len)
{
  t_vars vars;
  
  vars = mlx_creator(map, num_lines, line_len);
  vars.img = img_creator(&vars);
  printf("SCALAR %f\n", vars.img.scale);
  print_map(&(vars.img), map, num_lines , line_len);
  mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
  mlx_hook(vars.win, 2, 1L<<0, keypress_events, &vars);
  mlx_hook(vars.win, 17, 1L<<2, close_cross, &vars);
	mlx_loop(vars.mlx);
  mlx_destroy_image(vars.mlx, vars.img.img);
  mlx_destroy_window(vars.mlx, vars.win);
  free(vars.mlx);
}

int main(int argc, char **argv)
{
  int fd;
  t_point **map;
  int num_lines;
  int line_len;

  if (argc == 2)
  {
    fd = open(argv[1], O_RDONLY);
    if (fd > 0)
    {
      // 1. Parse the map
      map = parse_map(fd, &num_lines, &line_len);
      // print_map_struct(map, num_lines, line_len);

      // 2. Convert map to isometric projection
      rotation_z(map, num_lines, line_len, 3.14 + 0.785);
      rotation_x(map, num_lines, line_len, 3.14 + 0.955);

      //3. Create window and print map to window
      window(map, num_lines, line_len);
  
      //4. Freedom for all
      free_map_struct(map, num_lines);
    }
    else
      ft_printf("Invalid fd, could not read from map '%s'\n", argv[1]);
  }
  else
    ft_printf("Executable must be followed by a map name\n");
}
