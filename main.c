#include "fdf.h"

int main()
{
  int fd;
  point_t **map;

  fd = open("./test_maps/10-2.fdf", O_RDONLY);
  map = parse_map(fd);
  free_map_struct(map);
}
