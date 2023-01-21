#ifndef FDF_H
#define FDF_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct point_s {
  float x;
  float y;
  float z;
} point_t;

point_t **parse_map(int fd);
int **map_to_int(int fd, int **map, int *num_lines, int *line_len);
point_t **map_struct_creator(int num_lines, int line_len);
void map_int_to_struct(point_t **map_struct, int **map_int, int num_lines, int line_len);

void print_map_int(int **map, int num_lines, int line_len);
void print_map_struct(point_t **map, int line_len);
void free_map_struct(point_t **map);
void  free_map_int(int **map, int num_lines);
void free_line(char **line_split, char *line, int line_len);
#endif
