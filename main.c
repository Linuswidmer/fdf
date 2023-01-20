#include "fdf.h"

void print_map(int **map, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while(i < num_lines - 1)
  {
    while(j < line_len - 1)
    {
      ft_printf("%i", map[i][j]);
      j++;
    }
    j = 0;
    printf("\n");
    i++;
  }
}

int main()
{
  int **map;
  int fd;
  int num_lines;
  int line_len;

  fd = open("./test_maps/10-2.fdf", O_RDONLY);
  map = parse_map(fd, 0, &num_lines, &line_len);
  print_map(map, num_lines, line_len);
  free_map(map, num_lines);
}
