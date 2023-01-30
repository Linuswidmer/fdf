#include "fdf.h"

void free_map_int(int **map, int num_lines)
{
  int i;

  i = 0;
  while (i < num_lines)
  {
    free(map[i]);
    i++;
  }
  free(map);
}

void free_map_struct(t_point **map_struct, int num_lines)
{
  int i;

  i = 0;
  while (i < num_lines)
  {
    // printf("[%i] ", i);
    free(map_struct[i]);
    i++;
  }
  free(map_struct);
}

void free_line(char **line_split, char *line)
{
  int i;

  i = 0;
  while (line_split[i])
  {
    free (line_split[i]);
    i++;
  }
  free(line);
  free(line_split);
}
void print_map_int(int **map, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while(i < num_lines)
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

void print_map_struct(t_point **map_struct, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (i < num_lines)
  {
    while (j < line_len)
    {
      printf("[%2f], [%2f], [%2f]   ", (map_struct[i][j]).x, (map_struct[i][j]).y, (map_struct[i][j]).z);
      j++;
    }
    printf("\n");
    j = 0;
    i++;
  }
}
