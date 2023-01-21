#include "fdf.h"

void free_map_int(int **map, int num_lines)
{
  int i;

  i = 0;
  while (i < num_lines - 1)
  {
    free(map[i]);
    i++;
  }
  free(map);
}

void free_map_struct(point_t **map_struct)
{
  int i;

  i = 0;
  while (map_struct[i])
  {
    free(map_struct[i]);
    i++;
  }
  free(map_struct);
}

void free_line(char **line_split, char *line, int line_len)
{
  int i;

  i = 0;
  free(line);
  while (i < line_len)
  {
    free (line_split[i]);
    i++;
  }
  free(line_split);
}
void print_map_int(int **map, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while(i < num_lines - 1)
  {
    while(j < line_len)
    {
      ft_printf("%i", map[i][j]);
      j++;
    }
    j = 0;
    printf("\n");
    i++;
  }
}

void print_map_struct(point_t **map_struct, int line_len)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (map_struct[i])
  {
    while (j < line_len)
    {
      printf("[%i], [%i], [%i]   ", (int)(map_struct[i][j]).x, (int)(map_struct[i][j]).y, (int)(map_struct[i][j]).z);
      j++;
    }
    printf("\n");
    j = 0;
    i++;
  }
}
