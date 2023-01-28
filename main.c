#include "fdf.h"

int main(int argc, char **argv)
{
  int fd;
  t_point **map;
  int num_lines;
  int line_len;

  if (argc == 2)
  {
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
      ft_printf("Invalid fd, could not read from map '%s'\n", argv[1]);
      return (0);
    }
    // 1. Parse the map
    map = parse_map(fd, &num_lines, &line_len);
    // printf("MAP ADDRESS MAIN: %p\n", map);
    // print_map_struct(map, num_lines, line_len);

    // 2. Convert map to isometric projection


    //3. Create window and print map to window
    window(map, num_lines, line_len);
  
    //4. Freedom for all
    free_map_struct(map, num_lines);
  
    // print_edges_to_img(&img, edges);
  }
  else
    ft_printf("Executable must be followed by a map name\n");
}
