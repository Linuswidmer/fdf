#include <fdf.h>

void free_map(int **map, int num_lines)
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

static void free_line(char **line_split, char *line, int line_len)
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

static int *line_to_int(char **line, int *line_len)
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

int **parse_map(int fd, int **map, int *num_lines, int *line_len)
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
