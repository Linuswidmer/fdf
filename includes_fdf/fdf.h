#ifndef FDF_H
#define FDF_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int **parse_map(int fd, int **map, int *num_lines, int *line_len);
void  free_map(int **map, int num_lines);

#endif
