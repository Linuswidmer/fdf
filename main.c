#include "fdf.h"

int main()
{
  int fd;
  t_point **map;
  int num_lines;
  int line_len;

  // 1. Parse the map
  fd = open("./test_maps/10-2.fdf", O_RDONLY);
  map = parse_map(fd, &num_lines, &line_len);
  // print_map_struct(map, num_lines, line_len);

  // 2. Convert map to isometric projection

  //3. Create window and print map to window
  window(map, num_lines, line_len);

  // Draw lines to image
  
  //4. Freedom for all
  free_map_struct(map, num_lines);
  
  // print_edges_to_img(&img, edges);
}
