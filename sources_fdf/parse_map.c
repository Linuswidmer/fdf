/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:08:40 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/30 15:01:57 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*line_to_int(char **line, int *line_len)
{
	int	*line_int;
	int	i;

	i = 0;
	*line_len = 0;
	while (line[*line_len] && line[*line_len][0] != '\n')
	{
		(*line_len)++;
	}
	line_int = malloc(sizeof(int) * *line_len);
	if (!line_int)
		return (NULL);
	while (i < *line_len)
	{
		line_int[i] = ft_atoi(line[i]);
		i++;
	}
	return (line_int);
}

void	map_i_to_s(t_point **map_struct, int **map_int, int nl, int ll)
{
	int	i;
	int	j;

	i = 0;
	while (i < nl)
	{
		j = 0;
		while (j < ll)
		{
			(map_struct[i][j]).x = (float)i;
			(map_struct[i][j]).y = (float)j;
			(map_struct[i][j]).z = - (float)map_int[i][j];
			j++;
		}
		i++;
	}
}

t_point	**map_struct_creator(int num_lines, int line_len)
{
	t_point	**map_struct;
	t_point	*line;
	int		i;

	i = 0;
	map_struct = malloc(sizeof(map_struct) * num_lines);
	if (!map_struct)
		return (NULL);
	while (i < num_lines)
	{
		line = malloc(sizeof(t_point) * line_len);
		if (!line)
			return (NULL);
		map_struct[i] = line;
		i++;
	}
	return (map_struct);
}

int	**map_to_int(int fd, int **map, int *num_lines, int *line_len)
{
	char	*line;
	char	**line_split;
	int		**map_tmp;
	int		i;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		map_tmp = malloc(sizeof(map_tmp) * *num_lines);
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
		map = free_line(line_split, line, map, map_tmp);
		(*num_lines)++;
		line = get_next_line(fd);
	}
	return (map);
}
