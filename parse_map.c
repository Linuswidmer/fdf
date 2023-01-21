#include <fdf.h>

int *line_to_int(char **line, int *line_len)
{
  int *line_int;
  int i;

  i = 0;
  *line_len = 0;
  while (line[*line_len])
    (*line_len)++;
  line_int = malloc(sizeof(int) * *line_len);
  if (!line_int)
    return (NULL);
  while (line[i])
  {
    line_int[i] = ft_atoi(line[i]);
    i++;
  }
  return(line_int);
}

void  map_int_to_struct(point_t **map_struct, int **map_int, int num_lines, int line_len)
{
  int i;
  int j;

  i = 0;
  while (i < num_lines - 1)
  {
    j = 0;
    while (j < line_len)
    {
      (map_struct[i][j]).x = (float)i;
      (map_struct[i][j]).y = (float)j;
      (map_struct[i][j]).z = (float)map_int[i][j];
      j++;
    }
    i++;
  }
}

point_t **map_struct_creator(int num_lines, int line_len)
{
  point_t **map_struct;
  point_t *line;
  int i;

  i = 0;
  map_struct = malloc(sizeof(map_struct) * num_lines);
  if (!map_struct)
    return (NULL);
  // printf("SIZEOF LINE %li\n", sizeof(line));
  // sizeof line returns 8 while the real size is 12, no idea why
  while (i < num_lines - 1)
  {
    line = malloc(12 * line_len);
    if (!line)
        return (NULL);
    map_struct[i] = line;
    i++;
  }
  map_struct[i] = NULL; 
  return (map_struct);
  // last entry of struct map should be empty
}

int **map_to_int(int fd, int **map, int *num_lines, int *line_len)
{
  char *line;
  char **line_split;
  int **map_tmp;
  int i;

  *num_lines = 2;
  while ((line = get_next_line(fd)))
  {
    i = 0;
    map_tmp = malloc(sizeof(map_tmp) * *num_lines); // the last entry of map should be NULL
    if (!map_tmp)
      return (NULL);
    while (map && map[i])
    {
      map_tmp[i] = map[i];
      i++;
    }
    line_split = ft_split(line, ' ');
    map_tmp[i] = line_to_int(line_split, line_len);
    map_tmp[i + 1] = NULL;
    free(map);
    free_line(line_split, line, *line_len);
    map = map_tmp;
    (*num_lines)++;
  }
  *num_lines = *num_lines - 1;
  return(map);
}

point_t **parse_map(int fd)
{
  int **map_int;
  point_t **map_struct;
  int num_lines;
  int line_len;

  map_int = map_to_int(fd, 0, &num_lines, &line_len);
  line_len--;
  print_map_int(map_int, num_lines, line_len);
  map_struct = map_struct_creator(num_lines, line_len);
  map_int_to_struct(map_struct, map_int, num_lines, line_len);
  print_map_struct(map_struct, line_len);
  free_map_int(map_int, num_lines);
  return (map_struct);
}
