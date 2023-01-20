#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int *line_to_int(char **line)
{
  int line_len;
  int *line_int;
  int i;

  i = 0;
  line_len = 0;
  while (line[line_len])
    line_len++;
  line_int = malloc(sizeof(int) * line_len);
  if (!line_int)
    return (NULL);
  while (line[i])
  {
    line_int[i] = ft_atoi(line[i]);
    i++;
  }
  return(line_int);
}

int **parse_map(int fd, int **map)
{
  char *line;
  int **map_tmp;
  int map_size;
  int i;

  map_size = 2;
  while (line = get_next_line(fd))
  {
    i = 0;
    map_tmp = malloc(sizeof(map_tmp) * map_size); // the last entry of map should be NULL
    if (!map_tmp)
      return (NULL);
    while (map && map[i])
    {
      map_tmp[i] = map[i];
      i++;
    }
    map_tmp[i] = line_to_int(ft_split(line, ' '));
    map_tmp[i + 1] = NULL;
    free(map);
    free(line);
    map = map_tmp;
    map_size++;
  }
  return(map);
}

int main()
{
  int **map;
  int fd;
  int i;
  int j;

  i = 0;
  j = 0;
  map = 0;
  fd = open("./test_maps/10-2.fdf", O_RDONLY);
  map = parse_map(fd, map);
  while(i < 10)
  {
    while(j < 10)
    {
      ft_printf("%i", map[i][j]);
      j++;
    }
    j = 0;
    printf("\n");
    i++;
  }
  free(map);
  // line = ft_split(get_next_line(fd), ' ');
  // line_num = line_to_int(line);
  // while (i < 11)
  // {
  //   ft_printf("%i\n", line_num[i]);
  //   i++;
  // }
}
